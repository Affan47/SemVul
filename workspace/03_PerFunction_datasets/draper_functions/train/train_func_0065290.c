mc_discover_capabilities(Magicolor_Scanner *s)
{
	SANE_Status status;
	Magicolor_Device *dev = s->hw;

	SANE_String_Const *source_list_add = source_list;

	DBG(5, "%s\n", __func__);


	*source_list_add++ = FBF_STR;

	if (dev->cap->ADF)
		*source_list_add++ = ADF_STR;


	status = cmd_request_error(s);
	if (status != SANE_STATUS_GOOD)
		return status;

	dev->x_range = &dev->cap->fbf_x_range;
	dev->y_range = &dev->cap->fbf_y_range;

	DBG(5, "   x-range: %f %f\n", SANE_UNFIX(dev->x_range->min), SANE_UNFIX(dev->x_range->max));
	DBG(5, "   y-range: %f %f\n", SANE_UNFIX(dev->y_range->min), SANE_UNFIX(dev->y_range->max));

	DBG(5, "End of %s, status:%s\n", __func__, sane_strstatus(status));
	*source_list_add = NULL;
	return status;
}
