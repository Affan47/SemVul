e_cell_date_edit_thaw (ECellDateEdit *ecde)
{
	g_return_if_fail (E_IS_CELL_DATE_EDIT (ecde));

	if (ecde->freeze_count > 0) {
		ecde->freeze_count--;

		if (ecde->freeze_count == 0)
			e_cell_date_edit_rebuild_time_list (ecde);
	}
}
