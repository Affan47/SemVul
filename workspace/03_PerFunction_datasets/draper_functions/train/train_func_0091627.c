eti_get_index_at (AtkTable *table,
                  gint row,
                  gint column)
{
	ETableItem *item;

	item = E_TABLE_ITEM (eti_a11y_get_gobject (ATK_OBJECT (table)));
	if (!item)
		return -1;

	return column + (row + 1) * item->cols;
}
