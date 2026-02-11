show_range_float (CmdConfig *cmd_config, CameraWidget *range)
{
#ifdef HAVE_CDK_20010421
	return (show_range_int (cmd_config, range));
#else
        CDKFSCALE *fscale = NULL;
        float value, min, max, increment;
        const char *label;
        char title[1024];
        float selection;

        CHECK (gp_widget_get_value (range, &value));
        CHECK (gp_widget_get_label (range, &label));
        snprintf (title, sizeof (title), "<C></5>%s", label);
        CHECK (gp_widget_get_range (range, &min, &max, &increment));

        fscale = newCDKFScale (cmd_config->screen, CENTER, CENTER, title,
                               _("Value: "), A_STANDOUT,
                               50, value, min, max,
                               increment,
			       MAX (increment, (max - min) / 20.0),
			       get_digits (increment),
			       TRUE, FALSE);
        if (!fscale)
                return (GP_ERROR);

	selection = activateCDKFScale (fscale, 0);
        if (fscale->exitType == vNORMAL) {
		value = selection;
                gp_widget_set_value (range, &value);
                set_config (cmd_config);
        }

        destroyCDKFScale (fscale);
        return (GP_OK);
#endif
}
