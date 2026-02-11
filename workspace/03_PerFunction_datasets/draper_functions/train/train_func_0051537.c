pairxlatmove(REQUEST *req, VALUE_PAIR **to, VALUE_PAIR **from)
{
	VALUE_PAIR **tailto, *i, *j, *next;
	VALUE_PAIR *tailfrom = NULL;
	VALUE_PAIR *found;


	tailto = to;
	for (i = *to; i; i = i->next) {
		tailto = &i->next;
	}


	for (i = *from; i; i = next) {
		next = i->next;


		if (i->attribute == PW_FALL_THROUGH) {
			tailfrom = i;
			continue;
		}


		if (i->flags.do_xlat) {
			int rcode;
			char buffer[sizeof(i->vp_strvalue)];

			i->flags.do_xlat = 0;
			rcode = radius_xlat(buffer, sizeof(buffer),
					    i->vp_strvalue,
					    req, NULL);


			pairparsevalue(i, buffer);
		}

		found = pairfind(*to, i->attribute, i->vendor);
		switch (i->operator) {


			case T_OP_SUB:
				if (found) {
					if (!i->vp_strvalue[0] ||
				    	    (strcmp((char *)found->vp_strvalue,
					    	    (char *)i->vp_strvalue) == 0)) {
				  		pairdelete(to, found->attribute,
				  			found->vendor);


					tailto = to;
					for (j = *to; j; j = j->next) {
						tailto = &j->next;
					}
				}
			}
			tailfrom = i;
			continue;
			break;


			case T_OP_EQ:
				if (found) {
					tailfrom = i;
					continue;
				}
				break;


			case T_OP_SET:
				if (found) {
					VALUE_PAIR *vp;

					vp = found->next;
					memcpy(found, i, sizeof(*found));
					found->next = vp;
					tailfrom = i;
					continue;
				}
				break;


			default:
			case T_OP_ADD:
				break;
		}

		if (tailfrom) {
			tailfrom->next = next;
		} else {
			*from = next;
		}


		if (!*to) {
			tailto = to;
		}
		*tailto = i;
		if (i) {
			i->next = NULL;
			tailto = &i->next;
		}
	}
}
