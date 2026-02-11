layout_grid_compute(LayoutWindow *lw,
				GtkWidget *image, GtkWidget *tools, GtkWidget *files,
				GtkWidget **w1, GtkWidget **w2, GtkWidget **w3)
{


	if (layout_location_single(lw->dir_location))
		{
		if (layout_location_first(lw->dir_location))
			{
			*w1 = tools;
			layout_location_compute(lw->file_location, lw->image_location, files, image, w2, w3);
			}
		else
			{
			*w3 = tools;
			layout_location_compute(lw->file_location, lw->image_location, files, image, w1, w2);
			}
		}
	else if (layout_location_single(lw->file_location))
		{
		if (layout_location_first(lw->file_location))
			{
			*w1 = files;
			layout_location_compute(lw->dir_location, lw->image_location, tools, image, w2, w3);
			}
		else
			{
			*w3 = files;
			layout_location_compute(lw->dir_location, lw->image_location, tools, image, w1, w2);
			}
		}
	else
		{

		if (layout_location_first(lw->image_location))
			{
			*w1 = image;
			layout_location_compute(lw->file_location, lw->dir_location, files, tools, w2, w3);
			}
		else
			{
			*w3 = image;
			layout_location_compute(lw->file_location, lw->dir_location, files, tools, w1, w2);
			}
		}
}
