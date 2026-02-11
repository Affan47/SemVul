value_dump (GnmValue const *value)
{
	switch (value->type){
	case VALUE_EMPTY:
		g_print ("EMPTY\n");
		break;

	case VALUE_ERROR:
		g_print ("ERROR: %s\n", value->v_err.mesg->str);
		break;

	case VALUE_BOOLEAN:
		g_print ("BOOLEAN: %s\n", go_locale_boolean_name (value->v_bool.val));
		break;

	case VALUE_STRING:
		g_print ("STRING: %s\n", value->v_str.val->str);
		break;

	case VALUE_FLOAT:
		g_print ("NUMBER: %" GNM_FORMAT_f "\n", value_get_as_float (value));
		break;

	case VALUE_ARRAY: {
		int x, y;

		g_print ("Array: { ");
		for (y = 0; y < value->v_array.y; y++)
			for (x = 0; x < value->v_array.x; x++)
				value_dump (value->v_array.vals [x][y]);
		g_print ("}\n");
		break;
	}
	case VALUE_CELLRANGE: {


		GnmCellRef const *c = &value->v_range.cell.a;
		Sheet const *sheet = c->sheet;

		g_print ("CellRange\n");
		if (sheet && sheet->name_unquoted)
			g_print ("%s:", sheet->name_quoted);
		else
			g_print ("%p :", (void *)sheet);
		g_print ("%s%s%s%s\n",
			(c->col_relative ? "":"$"), col_name(c->col),
			(c->row_relative ? "":"$"), row_name(c->row));
		c = &value->v_range.cell.b;
		if (sheet && sheet->name_quoted)
			g_print ("%s:", sheet->name_unquoted);
		else
			g_print ("%p :", (void *)sheet);
		g_print ("%s%s%s%s\n",
			(c->col_relative ? "":"$"), col_name(c->col),
			(c->row_relative ? "":"$"), row_name(c->row));
		break;
	}
	default:
		g_print ("Unhandled item type\n");
	}
}
