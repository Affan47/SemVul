filter_apply_flags(struct filter *f, long flags)
{
    struct filter *s;
    if(!f) return;
    switch(f->type) {

      case F_SIBLIST:
	for(s = f->u.sib; s; s = s->next)
	    filter_apply_flags(s, flags);
	break;
      case F_SUBGROUP:
	filter_apply_flags(f->u.sub.list, flags);
	break;
      case F_NEG:
	filter_apply_flags(f->u.neg, flags);
	break;

      case F_SPORT: case F_DPORT:
	if(flags & FF_LOOKUP) {
	    struct port_spec *p = &f->u.ports;
	    if(p->min == -1) {
		fprintf(stderr, "warning: couldn't lookup service \"%s\"\n", p->minstr);
		break;
	    }
	    free(p->minstr);
	    p->minstr = int_to_str_dup(p->min);
	    if(p->maxstr) {
		if(p->max == -1) {
		    fprintf(stderr, "warning: couldn't lookup service \"%s\"\n", p->minstr);
		    break;
		}
		free(p->maxstr);
		p->maxstr = int_to_str_dup(p->max);
	    }
	}
	break;
      case F_SOURCE: case F_DEST:
	if(flags & FF_LOOKUP) {
	    struct addr_spec *a = &f->u.addrs;
	    struct hostent *h;
	    if(!(inet_aton(a->addrstr, &f->u.addrs.addr))) {

		if(!(h = gethostbyname(a->addrstr))) {
		    fprintf(stderr, "warning: can't lookup name \"%s\"\n", a->addrstr);
		} else {
		    free(a->addrstr);
		    a->addrstr = strdup(h->h_addr_list[0]);
		}
	    }
	}
	break;
      default: break;
    }
    filter_apply_flags(f->child, flags);
    filter_apply_flags(f->next, flags);
}
