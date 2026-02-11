spinner_increment_frame(SpinnerData *sp)
{
	sp->frame++;
	if (sp->frame >= g_list_length(sp->list)) sp->frame = 1;
	spinner_set_frame(sp, sp->frame);
}
