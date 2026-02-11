etgl_remove (ETableGroup *etg,
             gint row)
{
	ETableGroupLeaf *etgl = E_TABLE_GROUP_LEAF (etg);

	if (E_IS_TABLE_SUBSET_VARIABLE (etgl->ets)) {
		return e_table_subset_variable_remove (
			E_TABLE_SUBSET_VARIABLE (etgl->ets), row);
	}
	return FALSE;
}
