xlsx_CT_SheetProtection (GsfXMLIn *xin, xmlChar const **attrs)
{
	XLSXReadState *state = (XLSXReadState *)xin->user_state;
	gboolean sheet			= FALSE;
	gboolean objects		= FALSE;
	gboolean scenarios		= FALSE;
	gboolean formatCells		= TRUE;
	gboolean formatColumns		= TRUE;
	gboolean formatRows		= TRUE;
	gboolean insertColumns		= TRUE;
	gboolean insertRows		= TRUE;
	gboolean insertHyperlinks	= TRUE;
	gboolean deleteColumns		= TRUE;
	gboolean deleteRows		= TRUE;
	gboolean selectLockedCells	= FALSE;
	gboolean sort			= TRUE;
	gboolean autoFilter		= TRUE;
	gboolean pivotTables		= TRUE;
	gboolean selectUnlockedCells	= FALSE;

	for (; attrs != NULL && attrs[0] && attrs[1] ; attrs += 2)
		if (attr_bool (xin, attrs, "sheet", &sheet)) ;
		else if (attr_bool (xin, attrs, "objects", &objects)) ;
		else if (attr_bool (xin, attrs, "scenarios", &scenarios)) ;
		else if (attr_bool (xin, attrs, "formatCells", &formatCells)) ;
		else if (attr_bool (xin, attrs, "formatColumns", &formatColumns)) ;
		else if (attr_bool (xin, attrs, "formatRows", &formatRows)) ;
		else if (attr_bool (xin, attrs, "insertColumns", &insertColumns)) ;
		else if (attr_bool (xin, attrs, "insertRows", &insertRows)) ;
		else if (attr_bool (xin, attrs, "insertHyperlinks", &insertHyperlinks)) ;
		else if (attr_bool (xin, attrs, "deleteColumns", &deleteColumns)) ;
		else if (attr_bool (xin, attrs, "deleteRows", &deleteRows)) ;
		else if (attr_bool (xin, attrs, "selectLockedCells", &selectLockedCells)) ;
		else if (attr_bool (xin, attrs, "sort", &sort)) ;
		else if (attr_bool (xin, attrs, "autoFilter", &autoFilter)) ;
		else if (attr_bool (xin, attrs, "pivotTables", &pivotTables)) ;
		else if (attr_bool (xin, attrs, "selectUnlockedCells", &selectUnlockedCells)) ;

	g_object_set (state->sheet,
		"protected",				 sheet,
		"protected-allow-edit-objects",		 objects,
		"protected-allow-edit-scenarios",	 scenarios,
		"protected-allow-cell-formatting",	 formatCells,
		"protected-allow-column-formatting",	 formatColumns,
		"protected-allow-row-formatting",	 formatRows,
		"protected-allow-insert-columns",	 insertColumns,
		"protected-allow-insert-rows",		 insertRows,
		"protected-allow-insert-hyperlinks",	 insertHyperlinks,
		"protected-allow-delete-columns",	 deleteColumns,
		"protected-allow-delete-rows",		 deleteRows,
		"protected-allow-select-locked-cells",	 selectLockedCells,
		"protected-allow-sort-ranges",		 sort,
		"protected-allow-edit-auto-filters",	 autoFilter,
		"protected-allow-edit-pivottable",	 pivotTables,
		"protected-allow-select-unlocked-cells", selectUnlockedCells,
		NULL);
}
