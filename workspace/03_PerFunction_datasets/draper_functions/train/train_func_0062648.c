find_truecolor_visual(void)
{
    static int search_mask = VisualClassMask | VisualScreenMask;
    XVisualInfo search_template;
    XVisualInfo *mvisual_info;
    int num_visuals;
    int vis_num;
    int highest_bit_depth = 0;

    search_template.class = TrueColor;
    search_template.screen = scrn;

    mvisual_info =
	XGetVisualInfo(dpy, search_mask, &search_template, &num_visuals);

    G_message(_("found %d visuals of type TrueColor"), num_visuals);

    G_message(_("searching for highest bit depth"));

    for (vis_num = 0; vis_num < num_visuals; vis_num++) {
	if (mvisual_info[vis_num].depth <= highest_bit_depth)
	    continue;

	use_visual = mvisual_info[vis_num].visual;
	use_bit_depth = mvisual_info[vis_num].depth;
	highest_bit_depth = use_bit_depth;
    }

    XFree(mvisual_info);

    if (highest_bit_depth == 0)
	G_warning("unable to find a TrueColor visual\n");
    else
	G_message(_("selected %d bit depth"), use_bit_depth);
}
