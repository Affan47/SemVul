Draw( wxDC *dc )
{
    wxListItemDataList::compatibility_iterator node = m_items.GetFirst();
    wxCHECK_RET( node, _T("no subitems at all??") );

    bool highlighted = IsHighlighted();

    wxListItemAttr *attr = GetAttr();

    if ( SetAttributes(dc, attr, highlighted) )
#if ( !defined(__WXGTK20__) && !defined(__WXMAC__) )
    {
        dc->DrawRectangle( m_gi->m_rectHighlight );
    }
#else
    {
        if (highlighted)
        {
            int flags = wxCONTROL_SELECTED;
            if (m_owner->HasFocus()
#if defined( __WXMAC__ ) && !defined(__WXUNIVERSAL__) && wxOSX_USE_CARBON
                && IsControlActive( (ControlRef)m_owner->GetHandle() )
#endif
            )
                flags |= wxCONTROL_FOCUSED;
            wxRendererNative::Get().DrawItemSelectionRect( m_owner, *dc, m_gi->m_rectHighlight, flags );

        }
        else
        {
            dc->DrawRectangle( m_gi->m_rectHighlight );
        }
    }
#endif


#if 0
    dc->SetPen(*wxRED_PEN);
    dc->SetBrush(*wxTRANSPARENT_BRUSH);
    dc->DrawRectangle( m_gi->m_rectAll );
    dc->SetPen(*wxGREEN_PEN);
    dc->DrawRectangle( m_gi->m_rectIcon );
#endif

    wxListItemData *item = node->GetData();
    if (item->HasImage())
    {


        const wxRect& rectIcon = m_gi->m_rectIcon;

        m_owner->DrawImage(item->GetImage(), dc, rectIcon.x, rectIcon.y);
    }

    if (item->HasText())
    {
        const wxRect& rectLabel = m_gi->m_rectLabel;

        wxDCClipper clipper(*dc, rectLabel);
        dc->DrawText(item->GetText(), rectLabel.x, rectLabel.y);
    }
}
