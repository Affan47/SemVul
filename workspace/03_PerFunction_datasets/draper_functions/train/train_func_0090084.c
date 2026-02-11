GetValue(const wxString& nameOfVariable ) const
{
    wxString strExpression;
    strExpression << _T("(") << nameOfVariable << _T(")");
    strExpression << _T("([ \t\n\r\f\v])*([=])([ \t\n\r\f\v])*([0-9]+)([ \t\n\r\f\v])*([;])+");
    wxRegEx expression;

    if (!expression.Compile(strExpression))
    {
        return 0;
    }

    if (expression.Matches(m_text))
    {
        wxString strResult;
        strResult = expression.GetMatch(m_text);
        expression.ReplaceAll(&strResult, wxT("\\5"));
        long value;
        strResult.ToLong(&value);
        return value;
    }

    return 0;
}
