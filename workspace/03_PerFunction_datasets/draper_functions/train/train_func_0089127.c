UpdateItemSummary(unsigned int i) {
    ListEditItem* item = GetItem(i);
    if(item != NULL)
        listbox->SetString(i, item->GetSummaryText());
}
