free_duped_lump_list(struct lump* l)
{
	struct lump *r, *foo,*crt;
	while(l){
		crt=l;
		l=l->next;

		r=crt->before;
		while(r){
			foo=r; r=r->before;


			if (foo->flags!=LUMPFLAG_DUPED)
					free_lump(foo);
			pkg_free(foo);
		}
		r=crt->after;
		while(r){
			foo=r; r=r->after;
			if (foo->flags!=LUMPFLAG_DUPED)
				free_lump(foo);
			pkg_free(foo);
		}


		if (crt->flags!=LUMPFLAG_DUPED)
			free_lump(crt);
		pkg_free(crt);
	}
}
