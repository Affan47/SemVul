SetFlags (int flags) {
    if (flags & myFR_DOWN) {
        m_direction->SetSelection (1);
    }else{
        m_direction->SetSelection (0);
    }
    m_matchcase->SetValue ((flags & myFR_MATCHCASE) > 0);
    m_wholeword->SetValue ((flags & myFR_WHOLEWORD) > 0);
    m_findregex->SetValue ((flags & myFR_FINDREGEX) > 0);
    m_subfolder->SetValue ((flags & myFR_SUBFOLDER) > 0);
}
