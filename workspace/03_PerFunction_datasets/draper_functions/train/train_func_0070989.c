_gda_vconnection_get_table_data_by_unique_name (GdaVconnectionDataModel *cnc, const gchar *unique_name)
{
	GSList *list;
	for (list = cnc->priv->table_data_list; list; list = list->next) {
		if (!strcmp (((GdaVConnectionTableData*) list->data)->unique_name, unique_name))
			return (GdaVConnectionTableData*) list->data;
	}
	return NULL;
}
