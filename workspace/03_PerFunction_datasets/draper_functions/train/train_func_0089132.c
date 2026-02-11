GetItem(unsigned int i) const {
    if(i >= GetItemCount())
        return NULL;
    ListEditClientObj* clientobj = (ListEditClientObj*) listbox->GetClientObject(i);
    if(clientobj == NULL)
        return NULL;
    return clientobj->item;
}
