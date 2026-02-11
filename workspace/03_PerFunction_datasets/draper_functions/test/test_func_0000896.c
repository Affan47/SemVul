file_print_isl_int(__isl_take isl_printer *p, isl_int i)
{
	isl_int_print(p->file, i, p->width);
	return p;
}
