Group ()
{
	gcp::Document *pDoc = m_pView->GetDoc ();
	gcu::Dialog *dlg = pDoc->GetDialog ("group");
	if (dlg)
		dlg->Present ();
	else
		new gcpGroupDlg (pDoc, NULL);
}
