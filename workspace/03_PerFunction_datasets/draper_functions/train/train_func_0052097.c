add_to_hit_list(
gamut *s,
gtri **hlp,
gtri *cf
) {
	gtri *tp;
	gvert *c0 = cf->v[0];
	gvert *c1 = cf->v[1];


	tp = *hlp;

	FOR_ALL_ITEMS(gtri, tp) {
		gvert *v0 = tp->v[0];
		gvert *v1 = tp->v[1];
		if ((c0 == v0 && c1 == v1)
		 || (c0 == v1 && c1 == v0)) {


			DEL_LINK(*hlp, tp);


			if (cf->e[0] != tp->e[0]) {
				fprintf(stderr,"gamut: internal error - face match inconsistency\n");
				exit(-1);
			}

			DEL_LINK(s->edges, cf->e[0]);
			del_gedge(cf->e[0]);


			del_gtri(tp);
			del_gtri(cf);
			return;
		}
	} END_FOR_ALL_ITEMS(tp);


	ADD_ITEM_TO_BOT(*hlp, cf);

}
