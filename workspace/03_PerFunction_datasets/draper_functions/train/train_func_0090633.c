e_date_edit_set_date_internal (EDateEdit *dedit,
                               gboolean valid,
                               gboolean none,
                               gint year,
                               gint month,
                               gint day)
{
	EDateEditPrivate *priv;
	gboolean date_changed = FALSE;

	priv = dedit->priv;

	if (!valid) {

		if (priv->date_is_valid) {
			priv->date_is_valid = FALSE;
			date_changed = TRUE;
		}
	} else if (none) {

		if (!priv->date_is_valid
		    || !priv->date_set_to_none) {
			priv->date_is_valid = TRUE;
			priv->date_set_to_none = TRUE;
			date_changed = TRUE;
		}
	} else {

		if (!priv->date_is_valid
		    || priv->date_set_to_none
		    || priv->year != year
		    || priv->month != month
		    || priv->day != day) {
			priv->date_is_valid = TRUE;
			priv->date_set_to_none = FALSE;
			priv->year = year;
			priv->month = month;
			priv->day = day;
			date_changed = TRUE;
		}
	}

	return date_changed;
}
