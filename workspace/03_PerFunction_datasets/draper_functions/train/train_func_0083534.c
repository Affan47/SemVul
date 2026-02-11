report_range(void)
{
    char buff[1024], buff2[300];

    if (G_is_d_null_value(&old_dmin) || G_is_d_null_value(&old_dmax))
	G_message(_("Old data range is empty"));
    else {
	sprintf(buff, "%.10f", old_dmin);
	sprintf(buff2, "%.10f", old_dmax);
	G_trim_decimal(buff);
	G_trim_decimal(buff2);
	G_message(_("Old data range is %s to %s"), buff, buff2);
    }
    if (G_is_c_null_value(&old_min) || G_is_c_null_value(&old_max))
	G_message(_("Old integer data range is empty"));
    else
	G_message(_("Old integer data range is %d to %d"),
		  (int)old_min, (int)old_max);

    return 0;
}
