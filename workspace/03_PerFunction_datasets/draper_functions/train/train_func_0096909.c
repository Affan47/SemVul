new_gedge(void) {
	gedge *t;
	static int n = 0;
	if ((t = (gedge *) calloc(1, sizeof(gedge))) == NULL) {
		fprintf(stderr,"gamut: malloc failed - triangle edge\n");
		exit(-1);
	}
	t->n = n++;
	return t;
}
