LogWarningOrError(CompilerLineType lt, cbProject* prj, const wxString& filename, const wxString& line, const wxString& msg)
{

    wxArrayString errors;
    errors.Add(filename);
    errors.Add(line);

    wxString msgFix = msg; msgFix.Replace(wxT("\t"), wxT("    "));
    errors.Add(msgFix);

    Logger::level lv = (lt == cltError)   ? Logger::error
                     : (lt == cltWarning) ? Logger::warning : Logger::info;

    m_pListLog->Append(errors, lv, 2);


    m_Errors.AddError(lt, prj, filename, line.IsEmpty() ? 0 : atoi(wxSafeConvertWX2MB(line)), msg);
}
