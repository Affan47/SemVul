e_cal_component_get_categories_list (ECalComponent *comp,
                                     GSList **categ_list)
{
	ECalComponentPrivate *priv;
	icalproperty *prop;
	const gchar *categories;
	const gchar *p;
	const gchar *cat_start;
	gchar *str;

	g_return_if_fail (comp != NULL);
	g_return_if_fail (E_IS_CAL_COMPONENT (comp));
	g_return_if_fail (categ_list != NULL);

	priv = comp->priv;
	g_return_if_fail (priv->icalcomp != NULL);

	if (!priv->categories_str) {
		*categ_list = NULL;
		return;
	}

	*categ_list = NULL;

	for (prop = icalcomponent_get_first_property (priv->icalcomp, ICAL_CATEGORIES_PROPERTY);
	     prop;
	     prop = icalcomponent_get_next_property (priv->icalcomp, ICAL_CATEGORIES_PROPERTY)) {
		categories = icalproperty_get_categories (prop);
		g_return_if_fail (categories != NULL);

		cat_start = categories;

		for (p = categories; *p; p++) {
			if (*p == ',') {
				str = g_strndup (cat_start, p - cat_start);
				*categ_list = g_slist_prepend (*categ_list, str);

				cat_start = p + 1;
			}
		}

		str = g_strndup (cat_start, p - cat_start);
		*categ_list = g_slist_prepend (*categ_list, str);
	}

	*categ_list = g_slist_reverse (*categ_list);
}
