form_new_group(FormStack *st)
{
	FormGroup *fg;
	GF_SAFEALLOC(fg, FormGroup);
	memset(&fg->final, 0, sizeof(GF_Rect));
	memset(&fg->origin, 0, sizeof(GF_Rect));
	fg->children = gf_list_new();
	gf_list_add(st->grouplist, fg);
	return fg;
}
