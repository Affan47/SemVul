app_use_args(GSview *app, GSVIEW_ARGS *args)
{
    OPTION *opt = app_option(app);
    if (args->geometry) {
	if (args->geometry == 4) {
	    opt->img_origin.x = args->geometry_xoffset;
	    opt->img_origin.y = args->geometry_yoffset;
	}
	if (args->geometry >= 2) {
	    opt->img_size.x = args->geometry_width;
	    opt->img_size.y = args->geometry_height;
	}
    }
}
