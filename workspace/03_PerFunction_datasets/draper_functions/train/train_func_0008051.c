Apply(HighlightLanguage lang, cbStyledTextCtrl* control)
{
    if (!control)
        return;
    control->StyleClearAll();

    if (lang == HL_NONE)
        return;


    SOptionColour* defaults = GetOptionByName(lang, _T("Default"));
    if (defaults)
    {
        for (int i = 0; i < wxSCI_STYLE_MAX; ++i)
        {
            if (i < 33 || i > 39)
                DoApplyStyle(control, i, defaults);
        }
    }


    control->StyleSetForeground(wxSCI_STYLE_LINENUMBER, wxSystemSettings::GetColour(wxSYS_COLOUR_BTNTEXT));

    SOptionSet& mset = m_Sets[lang];
    for (unsigned int i = 0; i < mset.m_Colours.GetCount(); ++i)
    {
        SOptionColour* opt = mset.m_Colours.Item(i);

        if (opt->isStyle)
        {
            DoApplyStyle(control, opt->value, opt);
        }
        else
        {
            if (opt->value == cbHIGHLIGHT_LINE)
            {
                control->SetCaretLineBackground(opt->back);
                Manager::Get()->GetConfigManager(_T("editor"))->Write(_T("/highlight_caret_line_colour"), opt->back);
            }
            else if (opt->value == cbSELECTION)
            {
                if (opt->back != wxNullColour)
                {
                    control->SetSelBackground(true, opt->back);

                }
                else
                    control->SetSelBackground(false, wxColour(0xC0, 0xC0, 0xC0));

                if (opt->fore != wxNullColour)
                {
                    control->SetSelForeground(true, opt->fore);

                }
                else
                    control->SetSelForeground(false, *wxBLACK);
            }


        }
    }
    control->SetLexer(mset.m_Lexers);
    control->SetStyleBits(control->GetStyleBitsNeeded());
    for (int i = 0; i <= wxSCI_KEYWORDSET_MAX; ++i)
    {
        control->SetKeyWords(i, mset.m_Keywords[i]);
    }
    control->Colourise(0, -1);
}
