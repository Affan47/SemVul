init_paint_brush(GtkBuilder *builder)
{
	GtkWidget *brush;
	gchar name[20];
	gint i;
	static gint size[12] = {
							GP_BRUSH_RECT_LARGE,
							GP_BRUSH_RECT_MEDIUM,
							GP_BRUSH_RECT_SMALL,
							GP_BRUSH_ROUND_LARGE,
							GP_BRUSH_ROUND_MEDIUM,
							GP_BRUSH_ROUND_SMALL,
							GP_BRUSH_FWRD_LARGE,
							GP_BRUSH_FWRD_MEDIUM,
							GP_BRUSH_FWRD_SMALL,
							GP_BRUSH_BACK_LARGE,
							GP_BRUSH_BACK_MEDIUM,
							GP_BRUSH_BACK_SMALL,
						};

	if(NULL == builder){
		return;
	}

	for(i = 0; i < GP_BRUSH_MAX; i++)
	{
		sprintf(name, "brush%d", i);
		brush = GTK_WIDGET (gtk_builder_get_object (builder, name));
		if(!GTK_IS_WIDGET(brush))
		{
			printf("DEBUG: init_eraser() !GTK_IS_WIDGET(erase)\n");
		}
		g_signal_connect (brush, "toggled",
		            G_CALLBACK (on_brush_size_toggled), (gpointer)&(size[i]));
	}
}
