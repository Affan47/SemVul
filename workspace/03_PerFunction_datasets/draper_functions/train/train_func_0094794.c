aggregate_handle_float (CellData *cdata, gfloat val)
{
	if (cdata->data_value) {
		gfloat eval = 0;
		if (G_VALUE_TYPE (cdata->data_value) == G_TYPE_FLOAT)
			eval = g_value_get_float (cdata->data_value);
		switch (cdata->aggregate) {
		case GDA_DATA_PIVOT_MIN:
			if (eval > val)
				g_value_set_float (cdata->data_value, val);
			break;
		case GDA_DATA_PIVOT_MAX:
			if (eval < val)
				g_value_set_float (cdata->data_value, val);
			break;
		case GDA_DATA_PIVOT_SUM: {
			gdouble tmp;
			tmp = eval + val;
			if ((tmp > G_MAXDOUBLE) || (tmp < G_MINDOUBLE))
				g_set_error (&(cdata->error),
					     GDA_DATA_PIVOT_ERROR, GDA_DATA_PIVOT_OVERFLOW_ERROR,
					     "%s", _("Float value overflow"));
			else
				g_value_set_float (cdata->data_value, (gfloat) tmp);
			break;
		}
		case GDA_DATA_PIVOT_AVG: {
			gdouble tmp;
			tmp = g_value_get_double (cdata->data_value) + val;
			if ((tmp > G_MAXDOUBLE) || (tmp < G_MINDOUBLE))
				g_set_error (&(cdata->error),
					     GDA_DATA_PIVOT_ERROR, GDA_DATA_PIVOT_OVERFLOW_ERROR,
					     "%s", _("Float value overflow"));
			else
				g_value_set_double (cdata->data_value, tmp);
			break;
		}
		default:
			return FALSE;
		}
	}
	else {

		switch (cdata->aggregate) {
		case GDA_DATA_PIVOT_MIN:
		case GDA_DATA_PIVOT_MAX:
		case GDA_DATA_PIVOT_SUM:
			cdata->data_value = gda_value_new (G_TYPE_FLOAT);
			g_value_set_float (cdata->data_value, val);
			break;
		case GDA_DATA_PIVOT_AVG:
			cdata->data_value = gda_value_new (G_TYPE_DOUBLE);
			g_value_set_double (cdata->data_value, (gdouble) val);
			break;
		default:
			return FALSE;
		}
	}
	cdata->nvalues ++;
	return TRUE;
}
