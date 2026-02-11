on_update_video_widget()
{
	if(!full_screen && gmp_embed && gmp->running())
	{
		int n_width = play_frame->get_width();

		int w, h;
		gmp->get_size_request(w, h);

		int n_height = (int)n_width *gmp_rate;
		if (w + channels_box->get_width() > gdk_screen_width() - 20)  {
			if (n_height > h)
				n_height = h;
			if (w > gdk_screen_width() - 20) {
				n_width = gdk_screen_width() - 40;

				set_gmp_size(n_width,n_height);
			} else{
				;

				}
		}

		if (n_height == h)
			return;

		if (n_height < 0)
			return ;

		set_gmp_size(n_width,n_height);
	}
}
