elevator_update_doors(struct cpssp * cpssp)
{
	int i;

	for (i = 0; i < 3; i++) {
		gdk_pixbuf_composite(cpssp->pb_cabin, cpssp->doors[i].pixbuf, 0, 0, 49, 121,
				0.0, -1 * (cpssp->doors[i].offset + cpssp->cabin_pos),
				1.0, 1.0, GDK_INTERP_NEAREST, 255);

		gdk_pixbuf_composite(cpssp->pb_door_l, cpssp->doors[i].pixbuf, 0, 0, 25 - cpssp->doors[i].pos, 121,
				0.0, 0.0, 1.0, 1.0, GDK_INTERP_NEAREST, 255);
		gdk_pixbuf_composite(cpssp->pb_door_r, cpssp->doors[i].pixbuf,
				24 + cpssp->doors[i].pos, 0, 25 - cpssp->doors[i].pos, 121,
				0.0, 0.0, 1.0, 1.0, GDK_INTERP_NEAREST, 255);
		gtk_image_set_from_pixbuf(GTK_IMAGE(cpssp->doors[i].door), cpssp->doors[i].pixbuf);
	}
	gui_gtk_flush();
}
