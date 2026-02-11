OnBtnWriteClick(wxCommandEvent& )
{
    if (grdChanges->GetNumberRows() > 0)
    {
        for (int i=0; i<grdChanges->GetNumberRows(); ++i)
        {
            if (grdChanges->GetCellValue(i,0) != _T(""))
            {
                m_changes += grdChanges->GetCellValue(i,0) + _T(": ");
            }

            m_changes += grdChanges->GetCellValue(i,1);

            if(i != grdChanges->GetNumberRows()-1)
            {
                m_changes += _T("\n");
            }
        }

        wxRemoveFile(m_tempChangesFile);
        EndModal(0);
    }
    else
    {
        wxMessageBox(_("There are no rows in the data grid to write."), _("Error"), wxICON_ERROR );
    }
}
