NyquistToWxString(const char *nyqString)
{
    wxString str(nyqString, wxConvUTF8);
    if (nyqString != NULL && nyqString[0] && str.IsEmpty()) {

        str = _("[Warning: Nyquist returned invalid UTF-8 string, converted here as Latin-1]");
        str += LAT1CTOWX(nyqString);
    }
    return str;
}
