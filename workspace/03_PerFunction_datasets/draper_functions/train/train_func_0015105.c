getzMinzMax(GtkWidget* contoursplot, ContoursPlotData* data, gdouble* zmin, gdouble* zmax)
{
	*zmin = 0;
	*zmax = 0;
	if(data)
	{
		*zmin=data->zmin;
		*zmax=data->zmax;
	}
	if(contoursplot && GABEDIT_ContoursPLOT(contoursplot)->data_list)
	{
		gint ib = 0;
		GList *current_node;
		current_node=g_list_last(GABEDIT_ContoursPLOT(contoursplot)->data_list);
		if(current_node)
		{
			ContoursPlotData* data = (ContoursPlotData*)current_node->data;
			if(ib==0)
			{
				*zmin=data->zmin;
				*zmax=data->zmax;
			}
			else
			{
				ib = 1;
				if(*zmin>data->zmin) *zmin=data->zmin;
				if(*zmax<data->zmax) *zmax=data->zmax;
			}
		}
	}
}
