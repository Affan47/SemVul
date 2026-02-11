OnCommand(wxCommandEvent& event) {
    switch(event.GetId()) {
    case wxID_ADD:
        if(listbox != NULL && GetItemCount() < maxlen) {
            ListEditItem* newitem = GetNewItem();
            if(newitem == NULL)
                break;
            if(newitem->Edit(this))
                AddItem(newitem);
            else
                delete newitem;
        }
        break;
    case ID_EDIT:
        if(listbox != NULL) {
            int sel = listbox->GetSelection();
            if(sel == wxNOT_FOUND || sel < 0)
                break;
            ListEditItem* item = GetItem(sel);
            if(item == NULL)
                break;
            if(item->Edit(this))
                UpdateItemSummary(sel);
        }
        break;
    case wxID_REMOVE:
        if(listbox != NULL) {
            int sel = listbox->GetSelection();
            if(sel == wxNOT_FOUND || sel < 0)
                break;
            DeleteItem(sel);
        }
        break;
    case wxID_UP:
    case wxID_DOWN:
        if(listbox != NULL) {
            int sel = listbox->GetSelection();
            if(sel == wxNOT_FOUND || sel < 0)
                break;
            if(event.GetId() == wxID_UP && sel == 0)
                break;
            if(event.GetId() == wxID_DOWN && (unsigned int) sel == GetItemCount() - 1)
                break;
            ListEditItem* item = RemoveItem(sel);
            if(item == NULL)
                break;
            AddItem(item, sel + (event.GetId() == wxID_UP ? -1 : 1));
        }
        break;
    default:
        event.Skip();
    }
}
