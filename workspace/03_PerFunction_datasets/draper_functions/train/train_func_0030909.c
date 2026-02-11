inv_display_spec_set_bypass(InvDisplaySpec *display_spec, gint num)
{
	gint i;
	if(display_spec->bypass != num) {
		display_spec->bypass = num;
		for(i=0;i<31;i++) {
			display_spec->value[i]=-90;
		}
	}
}
