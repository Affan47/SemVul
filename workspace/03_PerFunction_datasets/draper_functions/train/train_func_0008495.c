generate_user_color_pixbuf(Gtk::Widget& w,
	                                                     gdouble hue)
	{
		Gtk::StockID id =
			Gobby::IconManager::STOCK_USER_COLOR_INDICATOR;

		Glib::RefPtr<Gdk::Pixbuf> pixbuf =
			Gobby::GtkCompat::render_icon(
				w, id,
				Gtk::ICON_SIZE_MENU);


		pixbuf = pixbuf->copy();

		for(int y = 0; y < pixbuf->get_height(); ++y)
		{
			for(int x = 0; x < pixbuf->get_width(); ++x)
			{
				guint8* pixels = pixbuf->get_pixels();
				guint8* pixel =
					pixels + y * pixbuf->get_rowstride() +
					         x * pixbuf->get_n_channels();

				double r = pixel[0]/255.0;
				double g = pixel[1]/255.0;
				double b = pixel[2]/255.0;

				Gobby::rgb_to_hsv(r,g,b);
				r = hue;
				Gobby::hsv_to_rgb(r,g,b);

				pixel[0] =
					static_cast<guint8>(r * 255.0 + 0.5);
				pixel[1] =
					static_cast<guint8>(g * 255.0 + 0.5);
				pixel[2] =
					static_cast<guint8>(b * 255.0 + 0.5);
			}
		}

		return pixbuf;
	}
}
