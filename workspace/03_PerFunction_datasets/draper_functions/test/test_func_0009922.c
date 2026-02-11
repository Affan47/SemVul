DeleteAll (G_GNUC_UNUSED CleavagesDlg *pBox)
{
	gcr_grid_delete_all (GCR_GRID (pBox->m_Grid));
	for (unsigned i = 0; i < pBox->m_Cleavages.size (); i++)
		delete pBox->m_Cleavages[i];
	pBox->m_Cleavages.clear ();
	pBox->m_pDoc->GetCleavageList ()->clear ();
	pBox->m_pDoc->Update ();
	pBox->m_pDoc->SetDirty (true);
	gtk_widget_set_sensitive (pBox->DeleteAllBtn, false);
}
