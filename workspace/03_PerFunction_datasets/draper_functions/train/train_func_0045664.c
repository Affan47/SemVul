print_fragment_chain(struct FRAGMENT * f)
{
	while (f) {
		printf ("%x(%i,%i)->",f,f->off,f->len);

		if (f == f->next) {
			printf ("inf\n");
			return 1;
		}
		f = f->next;
	}
	printf("NULL\n");
	return 0;
}
