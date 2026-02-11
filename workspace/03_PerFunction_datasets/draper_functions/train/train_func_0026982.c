OnNavigationKey(wxNavigationKeyEvent& event)
#endif
{

    if ( event.IsWindowChange() )
    {
        AdvanceSelection(event.GetDirection());
    }
    else
    {
#if wxCHECK_VERSION(2, 9, 0)
        wxAuiNotebook::OnNavigationKeyNotebook(event);
#else
        wxAuiNotebook::OnNavigationKey(event);
#endif
    }
}
