nullify_aux_return (parser *p)
{
    int i;

    if (p->aux != NULL) {
	for (i=0; i<p->n_aux; i++) {
	    if (p->aux[i] == p->ret) {
		p->aux[i] = NULL;
		return;
	    }
	}
    }
}
