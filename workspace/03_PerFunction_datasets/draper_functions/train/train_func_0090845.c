setup()
{
    FindFlags flags;
    if (!checkbox_wholeword->IsChecked())
        flags.remove(se::WHOLE_WORD);
    if (!checkbox_matchcase->IsChecked())
        flags.remove(se::MATCH_CASE);
    if (!checkbox_regexp->IsChecked())
        flags.remove(se::REGULAR_EXPRESSION);
    if (!checkbox_convertbs->IsChecked())
        flags.remove(se::CONVERT_BACKSLASH);
    if (!checkbox_wrap->IsChecked())
        flags.remove(se::WRAP);
    if (!checkbox_fromtop->IsChecked())
        flags.remove(se::FROM_TOP);

    wxString find = text_ctrl_find->GetValue();
    wxString replace = text_ctrl_replace->GetValue();
    parentEditorM->setupSearch(find, replace, flags);
    if (flags.has(se::FROM_TOP))
        checkbox_fromtop->SetValue(false);
}
