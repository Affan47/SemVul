OnListKeyDown(wxListEvent &event)
{
    switch ( event.GetKeyCode() )
    {
        case WXK_DELETE:
            RemoveSelected();
            break;

        case WXK_INSERT:


        default:

            event.Skip();
    }
}
