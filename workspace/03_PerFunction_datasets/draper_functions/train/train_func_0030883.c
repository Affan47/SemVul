Open(LoaderBase* fileLdr, const wxString& filename, int , ProjectFile* data)
{
    bool can_updateui = !GetActiveEditor() || !Manager::Get()->GetProjectManager()->IsLoading();
    wxFileName fn(realpath(filename));
    NormalizePath(fn, wxEmptyString);
    wxString fname = UnixFilename(fn.GetFullPath());

    if (!wxFileExists(fname))
        return nullptr;


    s_CanShutdown = false;

    EditorBase* eb = IsOpen(fname);
    cbEditor* ed = nullptr;
    if (eb)
    {
        if (eb->IsBuiltinEditor())
        {
            ed = (cbEditor*)eb;
        }
        else
        {
            s_CanShutdown = true;
            return nullptr;
        }
    }

    if (!ed)
    {
        if (!fileLdr)
            fileLdr = Manager::Get()->GetFileManager()->Load(filename);
        if (fileLdr)
        {
            ed = new cbEditor(m_pNotebook, fileLdr, fname, m_Theme);
            if (ed->IsOK())
                AddEditorBase(ed);
            else
            {
                ed->Destroy();
                ed = nullptr;
            }
        }
    }


    if (ed && !ed->GetProjectFile())
    {

        if (data)
            Manager::Get()->GetLogManager()->DebugLog(_T("Project data set for ") + data->file.GetFullPath());
        else
            Manager::Get()->GetProjectManager()->FindProjectForFile(ed->GetFilename(), &data, false, false);
        if (data)
            ed->SetProjectFile(data,true);
    }

    if (can_updateui)
    {
        if (ed)
        {
            SetActiveEditor(ed);
            ed->GetControl()->SetFocus();
        }
    }


    s_CanShutdown = true;

    return ed;
}
