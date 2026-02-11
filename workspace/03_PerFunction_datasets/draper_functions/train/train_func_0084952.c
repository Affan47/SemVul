gui_mch_flash(int msec)
{
    GdkGCValues	values;
    GdkGC	*invert_gc;

    if (gui.drawarea->window == NULL)
	return;

    values.foreground.pixel = gui.norm_pixel ^ gui.back_pixel;
    values.background.pixel = gui.norm_pixel ^ gui.back_pixel;
    values.function = GDK_XOR;
    invert_gc = gdk_gc_new_with_values(gui.drawarea->window,
				       &values,
				       GDK_GC_FOREGROUND |
				       GDK_GC_BACKGROUND |
				       GDK_GC_FUNCTION);
    gdk_gc_set_exposures(invert_gc,
			 gui.visibility != GDK_VISIBILITY_UNOBSCURED);


    gdk_draw_rectangle(gui.drawarea->window, invert_gc,
		       TRUE,
		       0, 0,
		       FILL_X((int)Columns) + gui.border_offset,
		       FILL_Y((int)Rows) + gui.border_offset);

    gui_mch_flush();
    ui_delay((long)msec, TRUE);

    gdk_draw_rectangle(gui.drawarea->window, invert_gc,
		       TRUE,
		       0, 0,
		       FILL_X((int)Columns) + gui.border_offset,
		       FILL_Y((int)Rows) + gui.border_offset);

    gdk_gc_destroy(invert_gc);
}
