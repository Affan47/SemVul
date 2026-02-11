operator<< (const SqlTokenType stt)
{
    wxString kw(SqlTokenizer::getKeyword(stt, keywordsUpperCaseM));
    if (lineWrappingM && currentLineM.Length() + kw.Length() > maxLineLengthM)
        addNewLine();
    currentLineM += kw;
    return (*this);
}
