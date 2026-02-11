__filter_unroll(struct filter *f)
{
    struct filter *c, *s;

    if(!f) return;


    __filter_unroll(c = f->child);


    switch(f->type) {
      case F_SIBLIST:
	for(s = f->u.sib; s; s = s->next) {
	    __filter_unroll(s);
	    filter_append(s, c);
	}
	f->child = NULL;
	break;
      case F_SUBGROUP:
	__filter_unroll(f->u.sub.list);
	break;
      case F_NEG: abort();
      default: break;
    }


    __filter_unroll(f->next);
}
