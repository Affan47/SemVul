AddItem(ListEditItem* newitem, unsigned int pos) {
    if(newitem != NULL) {
        if(listbox != NULL) {
            listbox->Insert(newitem->GetSummaryText(), pos, new ListEditClientObj(newitem));
            int i = pos;
            if(i >= 0 && (unsigned int) i < (unsigned int) listbox->GetCount()) {
                listbox->SetSelection(i);
                return;
            }
        }
        delete newitem;
    }
}
