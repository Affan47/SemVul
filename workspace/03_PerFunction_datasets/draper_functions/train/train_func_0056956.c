GetElapsedTimeString(double f) {
    wxString s = wxEmptyString;
    wxString str = wxEmptyString;

    if (f < 0) {
        s = m_sNotAvailableString;
    } else {
        s = FormatTime(f);
    }
    str.Printf(_("Elapsed: %s"), s.c_str());
    return str;
}
