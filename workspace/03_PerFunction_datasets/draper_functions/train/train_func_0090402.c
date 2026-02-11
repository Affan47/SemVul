ans(const char *text,int wanted,void *result,int res_len)
{
    unsigned char answer[MAX_ANSWER];
    char name[MAX_NAME];
    unsigned char *pos,*data,*found;
    int answer_len,name_len,data_len,found_len;
    int questions,answers;

    found_len = 0;
    if ((answer_len = res_search(text,C_IN,wanted,answer,MAX_ANSWER)) < 0)
	return TRY_OTHER;


    pos = answer+12;
    if (answer[3] & 15) return TRY_OTHER;
    questions = GET16(answer+4);
    if (questions != 1) return TRY_OTHER;
    answers = GET16(answer+6);
    if (answers < 1) return TRY_OTHER;


    if ((name_len = dn_expand(answer,answer+answer_len,pos,name,MAX_NAME)) < 0)
	return TRY_OTHER;
    pos += name_len;
    if (GET16(pos) != wanted || GET16(pos+2) != C_IN) return TRY_OTHER;
    pos += 4;


    found = NULL;
    while (answers--) {


	if ((name_len = dn_expand(answer,answer+answer_len,pos,name,MAX_NAME))
	  < 0) return TRY_OTHER;
	pos += name_len;
	data_len = GET16(pos+8);
	data = pos+10;
	pos = data+data_len;
	if (GET16(data-10) != wanted || GET16(data-8) != C_IN || !--data_len)
	    continue;
	switch (wanted) {
            case T_NSAP:
                data_len++;
                if (data_len != ATM_ESA_LEN) continue;
                memcpy(((struct sockaddr_atmsvc *) result)->
                  sas_addr.prv,data,ATM_ESA_LEN);
                return 0;
	    case T_ATMA:
		switch (*data++) {
		    case ATMA_AESA:
			if (data_len != ATM_ESA_LEN) continue;
			memcpy(((struct sockaddr_atmsvc *) result)->
			  sas_addr.prv,data,ATM_ESA_LEN);
			return 0;
		    case ATMA_E164:
			if (data_len > ATM_E164_LEN) continue;
			if (!found) {
			    found = data;
			    found_len = data_len;
			}
			break;
		    default:
			continue;
		}
	    case T_PTR:
		    if (dn_expand(answer,answer+answer_len,data,result,
		      res_len) < 0) return FATAL;
		    return 0;
		default:
		    continue;
	}
    }
    if (!found) return TRY_OTHER;
    memcpy(((struct sockaddr_atmsvc *) result)->sas_addr.pub,found,
      found_len);
    ((struct sockaddr_atmsvc *) result)->sas_addr.pub[found_len] = 0;
    return 0;
}
