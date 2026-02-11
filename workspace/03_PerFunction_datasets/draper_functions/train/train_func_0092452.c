file_util_details_cb(GenericDialog *gd, gpointer data)
{
	UtilityData *ud = data;
	if (ud->details_func && ud->sel_fd)
		{
		ud->details_func(ud, ud->sel_fd);
		}
}
