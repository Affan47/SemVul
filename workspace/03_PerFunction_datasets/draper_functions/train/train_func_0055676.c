SetMenuItems(std::vector<wxString> newitems) {
    unsigned int len = GetMaxLength();
    if(len > items.size())
        len = items.size();
    if(len < 1)
        len = 1;
    unsigned int newlen = GetMaxLength();
    if(newlen > newitems.size())
        newlen = newitems.size();
    if(newlen < 1)
        newlen = 1;
    for(std::set<wxMenu*>::const_iterator menuit = menus.begin(); menuit != menus.end(); ++menuit) {
        wxMenu* menu = *menuit;
        if(menu == NULL)
            continue;

        const wxMenuItemList& itemlist = menu->GetMenuItems();
        unsigned int indexmin;
        wxMenuItemList::const_iterator itemit;
        for(indexmin = 0, itemit = itemlist.begin(); itemit != itemlist.end(); ++indexmin, ++itemit) {
            wxMenuItem* item = *itemit;
            if(item != NULL && item->GetId() == idmin)
                break;
        }

        unsigned int i;
        for(i = 0; i < std::min(len, newlen) && itemit != itemlist.end(); ++i, ++itemit) {
            wxMenuItem* item = *itemit;
            if(item == NULL)
                continue;
            item->SetText(GetItemLabel(i, newitems, emptytext));
            item->Enable((unsigned int) i < newitems.size());
        }

        for(; i < newlen; ++i) {
            wxMenuItem* item = menu->Insert(indexmin + i, idmin + i, GetItemLabel(i, newitems, emptytext));
            if(item != NULL)
                item->Enable((unsigned int) i < newitems.size());
        }

        for(; i < len; ++i) {
            menu->Destroy(idmin + i);
        }
    }
    items.swap(newitems);
}
