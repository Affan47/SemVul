OnCommand(wxCommandEvent& event) {
    switch(event.GetId()) {
    case ID_BROWSE_PROGRAM:
        if(progbox != NULL) {
            wxString dirname;
            wxString filename = progbox->GetValue();
            if(filename.empty()) {
                if(dirbox != NULL)
                    dirname = dirbox->GetValue();
            } else {
                wxFileName filenamedetails(filename);
                dirname = filenamedetails.GetPath();
                filename = filenamedetails.GetFullName();
            }
            filename = wxFileSelector(wxT("Choose the program to run"), dirname, filename, wxT(""),
#ifdef __WXMSW__
                wxT("Executable files (*.exe)|*.exe|All files (*.*)|*.*")
#else
                wxT("*")
#endif
                , wxFD_OPEN | wxFD_FILE_MUST_EXIST, this);
            if(!filename.empty()) {
                progbox->ChangeValue(filename);
                if(dirbox != NULL) {
                    wxFileName filenamedetails(filename);
                    dirbox->ChangeValue(filenamedetails.GetPath());
                }
            }
        }
        break;
    case ID_BROWSE_WORKINGDIR:
        if(dirbox != NULL) {
            wxString dir = wxDirSelector(wxDirSelectorPromptStr, dirbox->GetValue(), wxDD_DEFAULT_STYLE | wxDD_DIR_MUST_EXIST, wxDefaultPosition, this);
            if(!dir.empty())
                dirbox->ChangeValue(dir);
        }
        break;
    case ID_DEFAULT_ARGS:
        if(argbox != NULL)
            argbox->ChangeValue(PlayTestType::GetDefaultArguments());
        break;
    case ID_TEST_SETTINGS:
        {

            if(!Validate() || !TransferDataFromWindow())
                break;

            LevelSet testlevelset;
            CountedPtr<Level> testlevel = testlevelset.CreateLevel();
            if(testlevel != NULL) {
                testlevel->title = "TEST";
                testlevel->hint = "This is a test of playtesting.";
                testlevel->psw = "TEST";
                testlevel->PlaceTileOnly(1, 1, TILE_CHIP_S);
                testlevel->PlaceTileOnly(3, 1, TILE_HINT);
                testlevel->PlaceTileOnly(5, 1, TILE_EXIT);
            }

            if(!type.Launch(testlevelset, testlevel->levelnumber))
                wxLogError(wxT("Playtesting failed."));
        }
        break;
    case wxID_HELP:
        LaunchHelp(wxT("playtest"));
        break;
    default:
        event.Skip();
    }
}
