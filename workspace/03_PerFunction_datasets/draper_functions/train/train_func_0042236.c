Define (unsigned nPage)
{
	gcu::Dialog *dialog;
	switch (nPage) {
	case 0:
		dialog = GetDialog ("cell");
		if (dialog)
			dialog->Present ();
		else
			new gcr::CellDlg (static_cast < Application * > (m_App), this);
		break;
	case 1:
		dialog = GetDialog ("atoms");
		if (dialog)
			dialog->Present ();
		else
			new gcr::AtomsDlg (static_cast <Application *> (m_App), this);
		break;
	case 2:
		dialog = GetDialog ("lines");
		if (dialog)
			dialog->Present ();
		else
			new gcr::LinesDlg (static_cast <Application *> (m_App), this);
		break;
	case 3:
		dialog = GetDialog ("size");
		if (dialog)
			dialog->Present ();
		else
			new gcr::SizeDlg (static_cast <Application *> (m_App), this);
		break;
	case 4:
		dialog = GetDialog ("cleavages");
		if (dialog)
			dialog->Present ();
		else
			new gcr::CleavagesDlg (static_cast < Application * > (m_App), this);
		break;
	}
}
