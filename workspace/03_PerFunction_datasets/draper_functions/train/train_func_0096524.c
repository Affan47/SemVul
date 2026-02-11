put_set(_set *s)
{
    int n = 0;

    while (s != NULL) {
	if (n % 4 == 0) fputc('\n', output_file);
	fprintf(output_file, "(%.4f,%.4f)", s->p->x, s->p->y);
	s = s->next;
	n++;
    }
    fputc('\n', output_file);
}
