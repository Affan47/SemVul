fztell(adv_fz* f)
{
	if (f->type == fz_file) {
		return ftell(f->f);
	} else {
		return f->virtual_pos;
	}
}
