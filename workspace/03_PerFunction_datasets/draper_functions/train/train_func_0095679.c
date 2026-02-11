list_account_compare_func (GtkTreeModel *model, GtkTreeIter *a, GtkTreeIter *b, gpointer userdata)
{
gint result = 0;
gint dt1, dt2;
Account *entry1, *entry2;


    gtk_tree_model_get(model, a,
    	LST_DSPACC_DATATYPE, &dt1,
    	LST_DSPACC_DATAS, &entry1,

    	-1);
    gtk_tree_model_get(model, b,
    	LST_DSPACC_DATATYPE, &dt2,
    	LST_DSPACC_DATAS, &entry2,

    	-1);

	if( dt1 == DSPACC_TYPE_NORMAL && dt2 == DSPACC_TYPE_NORMAL )
	{
		result = entry1->pos - entry2->pos;
	}


    return result;
}
