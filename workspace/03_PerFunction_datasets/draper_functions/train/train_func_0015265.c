img_get_text_animation_list( TextAnimation **animations )
{
	TextAnimation *list;
	gint           no_animations = 7;
	gint           i = 0;

	if( animations )
	{


		list = g_slice_alloc( sizeof( TextAnimation ) * no_animations );


		list[i].name   = g_strdup( _("None") );
		list[i].id     = i;
		list[i++].func = NULL;

		list[i].name   = g_strdup( _("Fade") );
		list[i].id     = i;
		list[i++].func = img_text_ani_fade;

		list[i].name   = g_strdup( _("Slide from left") );
		list[i].id     = i;
		list[i++].func = img_text_from_left;

		list[i].name   = g_strdup( _("Slide from right") );
		list[i].id     = i;
		list[i++].func = img_text_from_right;

		list[i].name   = g_strdup( _("Slide from top") );
		list[i].id     = i;
		list[i++].func = img_text_from_top;

		list[i].name   = g_strdup( _("Slide from bottom") );
		list[i].id     = i;
		list[i++].func = img_text_from_bottom;

		list[i].name   = g_strdup( _("Grow") );
		list[i].id     = i;
		list[i++].func = img_text_grow;


		*animations = list;
	}

	return( no_animations );
}
