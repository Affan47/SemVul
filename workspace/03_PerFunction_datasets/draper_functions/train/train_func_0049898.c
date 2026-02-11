GetMenuById(long menuId, bool recreate = false)
    {
        wxMenuBar* mbar = Manager::Get()->GetAppFrame()->GetMenuBar();
        if (!mbar)
            return nullptr;
        wxMenuItem *item = mbar->FindItem(menuId);
        if (!item)
            return nullptr;
        if (recreate)
        {
            wxMenu *menu = item->GetMenu();
            int pos = wxNOT_FOUND;
            for (size_t ii = 0; ii < menu->GetMenuItemCount(); ++ii)
            {
                if (item == menu->FindItemByPosition(ii))
                {
                    pos = ii;
                    break;
                }
            }
            if (pos != wxNOT_FOUND)
            {
                wxMenu *newSubMenu = new wxMenu;
                wxMenuItem *newItem = new wxMenuItem(menu, item->GetId(), item->GetItemLabelText(), item->GetHelp(),
                                                     item->GetKind(), newSubMenu);
                menu->Insert(pos, newItem);

                menu->Destroy(item);
                return newItem->GetSubMenu();
            }
        }
        return item ? item->GetSubMenu() : nullptr;
    }
}
