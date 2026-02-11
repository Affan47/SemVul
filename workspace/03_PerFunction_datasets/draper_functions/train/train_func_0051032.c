OnLinkClicked( wxHtmlLinkEvent& event )
{

    NoticeListCtrlEvent evt(
        wxEVT_NOTICELIST_ITEM_DISPLAY,
        event.GetInt(),
        event.GetLinkInfo().GetHref()
    );
    evt.SetEventObject(this);

    GetParent()->AddPendingEvent( evt );
}
