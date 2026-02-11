gf_box_dump_done(char *name, GF_Box *ptr, FILE *trace)
{
	if (ptr && ptr->other_boxes) {
		gf_box_array_dump(ptr->other_boxes, trace);
	}
	if (name)
		fprintf(trace, "</%s>\n", name);
}
