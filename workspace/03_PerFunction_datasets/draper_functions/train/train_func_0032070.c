gcr_collection_model_set_sort_column_id (GtkTreeSortable *sortable,
                                         gint sort_column_id,
                                         GtkSortType order)
{
	GcrCollectionModel *self = GCR_COLLECTION_MODEL (sortable);
	GCompareDataFunc func;
	gpointer argument;
	const GcrColumn *column;
	gboolean reverse;

	reverse = (order == GTK_SORT_DESCENDING);

	if (sort_column_id == GTK_TREE_SORTABLE_UNSORTED_SORT_COLUMN_ID) {
		func = reverse ? order_sequence_as_unsorted_reverse : order_sequence_as_unsorted;
		argument = NULL;

	} else if (sort_column_id == GTK_TREE_SORTABLE_DEFAULT_SORT_COLUMN_ID) {
		func = reverse ? order_sequence_by_closure_reverse : order_sequence_by_closure;
		argument = &self->pv->default_sort_closure;

	} else if (sort_column_id >= 0 && sort_column_id < self->pv->n_columns) {
		if (self->pv->column_sort_closures[sort_column_id].sort_func) {
			func = reverse ? order_sequence_by_closure_reverse : order_sequence_by_closure;
			argument = &self->pv->column_sort_closures[sort_column_id];
		} else {
			column = &self->pv->columns[sort_column_id];
			if (!(column->flags & GCR_COLUMN_SORTABLE))
				return;
			if (!lookup_compare_func (column->property_type)) {
				g_warning ("no sort implementation defined for type '%s' on column '%s'",
				           g_type_name (column->property_type), column->property_name);
				return;
			}

			func = reverse ? order_sequence_by_property_reverse : order_sequence_by_property;
			argument = (gpointer)column;
		}
	} else {
		g_warning ("invalid sort_column_id passed to gtk_tree_sortable_set_sort_column_id(): %d",
		           sort_column_id);
		return;
	}

	if (sort_column_id != self->pv->sort_column_id ||
	    order != self->pv->sort_order_type) {
		self->pv->sort_column_id = sort_column_id;
		self->pv->sort_order_type = order;
		gtk_tree_sortable_sort_column_changed (sortable);
	}

	if (func != self->pv->order_current ||
	    argument != self->pv->order_argument) {
		self->pv->order_current = func;
		self->pv->order_argument = (gpointer)argument;
		collection_resort_sequence (self, NULL, self->pv->root_sequence);
	}
}
