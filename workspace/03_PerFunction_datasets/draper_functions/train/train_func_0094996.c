GetInputList(cbProject *prj, wxFileName fnDoxyfile)
{

    wxArrayString asExtList;
    asExtList.Add(wxT("*.c"));
    asExtList.Add(wxT("*.cc"));
    asExtList.Add(wxT("*.cxx"));
    asExtList.Add(wxT("*.cpp"));
    asExtList.Add(wxT("*.c++"));
    asExtList.Add(wxT("*.java"));
    asExtList.Add(wxT("*.ii"));
    asExtList.Add(wxT("*.ixx"));
    asExtList.Add(wxT("*.ipp"));
    asExtList.Add(wxT("*.i++"));
    asExtList.Add(wxT("*.inl"));
    asExtList.Add(wxT("*.h"));
    asExtList.Add(wxT("*.hh"));
    asExtList.Add(wxT("*.hxx"));
    asExtList.Add(wxT("*.hpp"));
    asExtList.Add(wxT("*.h++"));
    asExtList.Add(wxT("*.idl"));
    asExtList.Add(wxT("*.odl"));
    asExtList.Add(wxT("*.cs"));
    asExtList.Add(wxT("*.php"));
    asExtList.Add(wxT("*.php3"));
    asExtList.Add(wxT("*.inc"));
    asExtList.Add(wxT("*.m"));
    asExtList.Add(wxT("*.mm"));
    asExtList.Add(wxT("*.py"));
    asExtList.Add(wxT("*.f90"));


     wxString sInputList;
     const int cntExtList = asExtList.GetCount();

     sInputList += wxT("INPUT                  = ");

    for (FilesList::iterator it = prj->GetFilesList().begin(); it != prj->GetFilesList().end(); ++it)
    {
        ProjectFile* prjFile = *it;
        if(prjFile)
        {
            const wxString sFileName = prjFile->relativeFilename;
            wxFileName fnFileName = prjFile->file;
            fnFileName.MakeRelativeTo(fnDoxyfile.GetPath());
            const wxString RelName = fnFileName.GetFullPath();


            for(int n = 0; n < cntExtList; ++n)
            {
               if(sFileName.Matches(asExtList.Item(n)))
               {
                  sInputList += wxT("\\\n\t\"") + RelName + wxT("\" ");
                  break;
               }
            }
        }
    }
     sInputList += wxT("\n");
     return sInputList;
}
