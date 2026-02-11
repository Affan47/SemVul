DeleteAll (LinesDlg *pBox)
{
	gcr_grid_delete_all (pBox->m_Grid);
	for (unsigned i = 0; i < pBox->m_Lines.size (); i++)
		delete pBox->m_Lines[i];
	pBox->m_Lines.clear ();
	pBox->m_pDoc->GetLineList ()->clear ();
	pBox->m_pDoc->Update ();
	pBox->m_pDoc->SetDirty (true);
	gtk_widget_set_sensitive (pBox->DeleteAllBtn, false);
}
