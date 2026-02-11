file_end_line(__isl_take isl_printer *p)
{
	fprintf(p->file, "%s\n", p->suffix ? p->suffix : "");
	return p;
}
