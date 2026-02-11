render2d_del(render2d *s) {
	prim2d *th, *nx;


	for (th = s->head; th != NULL; th = nx) {
		nx = th->next;
		th->del(th);
	}


	free(s);
}
