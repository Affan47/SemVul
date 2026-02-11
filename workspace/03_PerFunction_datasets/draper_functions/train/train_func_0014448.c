OnUnitChanged (PrintSetupDlg *dlg)
{
	GtkTreeIter iter;
	if (gtk_combo_box_get_active_iter (dlg->m_UnitBox, &iter)) {
		GtkUnit unit;
		gtk_tree_model_get (GTK_TREE_MODEL (dlg->m_UnitList), &iter, 1, &unit, -1);
		dlg->m_Printable->SetUnit (unit);
		UpdatePageSetup (NULL, dlg);
	}
}
