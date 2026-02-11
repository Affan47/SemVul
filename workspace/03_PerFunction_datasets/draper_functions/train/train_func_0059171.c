show_range_int (CmdConfig *cmd_config, CameraWidget *range)
{
	CDKSLIDER *slider = NULL;
	float value, min, max, increment;
	const char *label;
	char title[1024];
	int selection;

	CHECK (gp_widget_get_value (range, &value));
	CHECK (gp_widget_get_label (range, &label));
	snprintf (title, sizeof (title), "<C></5>%s", label);
	CHECK (gp_widget_get_range (range, &min, &max, &increment));

	slider = newCDKSlider (cmd_config->screen, CENTER, CENTER, title,
			       _("Value: "), '-',
			       50, (int) value, min, max,
			       increment,
			       MAX (increment, (max - min)/20.0),
			       TRUE,
			       FALSE);
	if (!slider)
		return (GP_ERROR);

	selection = activateCDKSlider (slider, 0);
	if (slider->exitType == vNORMAL) {
		value = selection;
		gp_widget_set_value (range, &value);
		set_config (cmd_config);
	}

	destroyCDKSlider (slider);
	return (GP_OK);
}
