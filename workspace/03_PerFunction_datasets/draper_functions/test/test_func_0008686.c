OnProperties(cb_unused wxCommandEvent& event)
{
    ScbEditor* ed = GetBuiltinActiveEditor();
    ProjectFile* pf = 0;
    if (ed)
        pf = ed->GetProjectFile();
    if (pf)
        pf->ShowOptions(Manager::Get()->GetAppWindow());
    else
    {


        EditProperties dlg(m_pParent, GetBuiltinActiveEditor());

    }
}
