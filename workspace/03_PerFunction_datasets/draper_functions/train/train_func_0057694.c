ModifyScrollBars(int nMax, int nPage) {
    bool modified = false;

    int vertEnd = nMax;
    if (!verticalScrollBarVisible)
        vertEnd = 0;


    if (sci->m_vScrollBar == NULL) {
        int  sbMax    = sci->GetScrollRange(wxVERTICAL);
        int  sbThumb  = sci->GetScrollThumb(wxVERTICAL);
        int  sbPos    = sci->GetScrollPos(wxVERTICAL);
        if (sbMax != vertEnd || sbThumb != nPage) {
            sci->SetScrollbar(wxVERTICAL, sbPos, nPage, vertEnd+1);
            modified = true;
        }
    }
    else {
        int  sbMax    = sci->m_vScrollBar->GetRange();
        int  sbPage   = sci->m_vScrollBar->GetPageSize();
        int  sbPos    = sci->m_vScrollBar->GetThumbPosition();
        if (sbMax != vertEnd || sbPage != nPage) {
            sci->m_vScrollBar->SetScrollbar(sbPos, nPage, vertEnd+1, nPage);
            modified = true;
        }
    }


    PRectangle rcText = GetTextRectangle();
    int horizEnd = scrollWidth;
    if (horizEnd < 0)
        horizEnd = 0;
    if (!horizontalScrollBarVisible || Wrapping())
        horizEnd = 0;
    int pageWidth = rcText.Width();

    if (sci->m_hScrollBar == NULL) {
        int sbMax    = sci->GetScrollRange(wxHORIZONTAL);
        int sbThumb  = sci->GetScrollThumb(wxHORIZONTAL);
        int sbPos    = sci->GetScrollPos(wxHORIZONTAL);
        if ((sbMax != horizEnd) || (sbThumb != pageWidth) || (sbPos != 0)) {
            sci->SetScrollbar(wxHORIZONTAL, sbPos, pageWidth, horizEnd);
            modified = true;
            if (scrollWidth < pageWidth) {
                HorizontalScrollTo(0);
            }
        }
    }
    else {
        int sbMax    = sci->m_hScrollBar->GetRange();
        int sbThumb  = sci->m_hScrollBar->GetPageSize();
        int sbPos    = sci->m_hScrollBar->GetThumbPosition();
        if ((sbMax != horizEnd) || (sbThumb != pageWidth) || (sbPos != 0)) {
            sci->m_hScrollBar->SetScrollbar(sbPos, pageWidth, horizEnd, pageWidth);
            modified = true;
            if (scrollWidth < pageWidth) {
                HorizontalScrollTo(0);
            }
        }
    }

    return modified;
}
