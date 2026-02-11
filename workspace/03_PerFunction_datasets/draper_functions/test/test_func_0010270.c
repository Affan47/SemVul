MaxZEdited (SizeDlg *pBox)
{
	g_signal_handler_block (pBox->MaxZ, pBox->m_MaxZFocusOutSignalID);
	double xmin, xmax, ymin, ymax, zmin, zmax, value;
	pBox->m_pDoc->GetSize (&xmin, &xmax, &ymin, &ymax, &zmin, &zmax);
	if (pBox->GetNumber (pBox->MaxZ, &value, gcugtk::Min, zmin) && zmax != value) {
		pBox->m_pDoc->SetSize (xmin, xmax, ymin, ymax, zmin, value);
		pBox->m_pDoc->Update ();
		pBox->m_pDoc->SetDirty (true);
	}
	g_signal_handler_unblock (pBox->MaxZ, pBox->m_MaxZFocusOutSignalID);
	return false;
}
