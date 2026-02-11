eti_get_column_at_index (AtkTable *table,
                         gint index)
{
	ETableItem *item;

	item = E_TABLE_ITEM (eti_a11y_get_gobject (ATK_OBJECT (table)));
	if (!item)
		return -1;

	return index % item->cols;
}
