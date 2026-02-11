supbook_get_sheet (GnmXLImporter *importer, gint16 sup_index, unsigned i)
{
	if (sup_index < 0) {
		g_warning ("external references not supported yet.");
		return NULL;
	}


	if (i >= 0xffff)
		return XL_EXTERNSHEET_MAGIC_DELETED;


	if (i == 0xfffe)
		return XL_EXTERNSHEET_MAGIC_SELFREF;

	g_return_val_if_fail ((unsigned)sup_index < importer->v8.supbook->len, NULL);

	switch (g_array_index (importer->v8.supbook, ExcelSupBook, sup_index).type) {
	case EXCEL_SUP_BOOK_SELFREF: {
		Sheet *sheet;
		g_return_val_if_fail (i < importer->boundsheet_sheet_by_index->len, NULL);
		sheet = g_ptr_array_index (importer->boundsheet_sheet_by_index, i);
		g_return_val_if_fail (IS_SHEET (sheet), NULL);
		return sheet;
	}
	case EXCEL_SUP_BOOK_STD:
		g_warning ("external references not supported yet.");
		break;
	case EXCEL_SUP_BOOK_PLUGIN:
		g_warning ("strange external reference.");
		break;
	}

	return XL_EXTERNSHEET_MAGIC_DELETED;
}
