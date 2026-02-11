destroy()
{
	if(buf_pixmap)
		gdk_pixmap_unref(buf_pixmap);
	for(int i = 0; i < NUM_BALLS; i++)
	{
		gdk_pixmap_unref(balls_pixmaps[i]);
		gdk_bitmap_unref(balls_pixmap_masks[i]);
	}

	gdk_colormap_free_colors(colormap, table_color, 1);

	gdk_colormap_free_colors(colormap, message_colours[1], 1);
	gdk_colormap_free_colors(colormap, message_colours[2], 1);
	gdk_colormap_free_colors(colormap, message_colours[3], 1);
	gdk_colormap_free_colors(colormap, message_colours[4], 1);
	gdk_colormap_free_colors(colormap, message_colours[14], 1);

	close_sound_device();
}
