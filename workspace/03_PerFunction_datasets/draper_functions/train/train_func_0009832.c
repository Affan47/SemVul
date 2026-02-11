resize_image (std::string widget_image, guint max_width,
						 guint max_height)
{
	guint cur_width = 0, cur_height = 0;


	GObject *widget = G_OBJECT (get (widget_image.c_str ()));
	if (!widget)
		return false;


	GtkImageAnimation *anim;
	anim = static_cast<GtkImageAnimation *>( g_object_get_data (widget, "_animation_") );
	if (!anim)
		return false;


	cur_width = anim->scaled_width ();
	cur_height = anim->scaled_height ();


	gboolean resize = false;
	if (cur_width > max_width) {
		cur_height = cur_height * max_width / cur_width;
		cur_width  = max_width;
		resize  = true;
	}
	if (cur_height > max_height) {
		cur_width  = cur_width * max_height / cur_height;
		cur_height = max_height;
		resize  = true;
	}


	if (resize)
		anim->resize (cur_width, cur_height);
	return true;
}
