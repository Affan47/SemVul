AddCompilerPredefinedMacrosVC(const wxString& compilerId, wxString& defs)
{
    static wxString vcDefs;
    static bool     firstExecute = true;
    if (firstExecute)
    {
        firstExecute = false;
        Compiler* compiler = CompilerFactory::GetCompiler(compilerId);
        if (!compiler)
            return false;

        wxString masterPath = compiler->GetMasterPath();
        Manager::Get()->GetMacrosManager()->ReplaceMacros(masterPath);
        const wxString c_compiler = masterPath + _T("\\bin\\") + compiler->GetPrograms().C;
        if ( !wxFileName::FileExists(c_compiler) )
            return false;

        static bool reentry = false;
        if (reentry)
            return false;

        wxArrayString output, error;
        reentry = true;


        if ( wxExecute(c_compiler, output, error, wxEXEC_SYNC | wxEXEC_NODISABLE) == -1 )
        {
            TRACE(_T("AddCompilerPredefinedMacrosVC::wxExecute failed!"));
            reentry = false;
            return false;
        }
        reentry = false;


        if ( Manager::IsAppShuttingDown() )
            return false;

        if (error.IsEmpty())
        {
            TRACE(_T("AddCompilerPredefinedMacrosVC:: Can't get pre-defined macros for MSVC."));
            return false;
        }

        wxString str = error[0];
        wxString tmp(_T("Microsoft (R) "));
        int pos = str.Find(tmp);
        if (pos != wxNOT_FOUND)
        {
            wxString bit = str.Mid(pos + tmp.Length(), 2);
            if (bit == _T("32"))
                defs += _T("#define _WIN32") _T("\n");
            else if (bit == _T("64"))
                defs += _T("#define _WIN64") _T("\n");
        }

        tmp = _T("Compiler Version ");
        pos = str.Find(tmp);
        if (pos != wxNOT_FOUND)
        {
            wxString ver = str.Mid(pos + tmp.Length(), 4);
            pos = ver.Find(_T('.'));
            if (pos != wxNOT_FOUND)
            {

                ver[pos]     = ver[pos + 1];
                ver[pos + 1] = _T('0');
                defs += _T("#define _MSC_VER ") + ver;


            }
        }
    }

    defs = vcDefs;

    return true;
}
