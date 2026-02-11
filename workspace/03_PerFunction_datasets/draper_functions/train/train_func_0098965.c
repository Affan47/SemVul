OnAEdited (CellDlg *dlg)
{
	g_signal_handler_block (dlg->A, dlg->ASignal);
	Lattice lattice;
	double val, a, b, c, alpha, beta, gamma;
	dlg->m_pDoc->GetCell (&lattice, &a, &b, &c, &alpha, &beta, &gamma);
	if (dlg->GetNumber (dlg->A, &val, gcugtk::Min, 0) && val != a) {
		switch (lattice) {
		case cubic:
		case body_centered_cubic:
		case face_centered_cubic:
		case rhombohedral:
			c = val;
			gtk_entry_set_text (dlg->C, gtk_entry_get_text (dlg->A));
		case hexagonal:
		case tetragonal:
		case body_centered_tetragonal:
			b = val;
			gtk_entry_set_text (dlg->B, gtk_entry_get_text (dlg->A));
			break;
		default:
			break;
		}
		dlg->m_pDoc->SetCell (lattice, val, b, c, alpha, beta, gamma);
		dlg->m_pDoc->Update ();
		dlg->m_pDoc->SetDirty (true);
	}
	g_signal_handler_unblock (dlg->A, dlg->ASignal);
	return false;
}
