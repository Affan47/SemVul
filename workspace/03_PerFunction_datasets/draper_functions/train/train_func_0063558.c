prepareTemplateItems(Player* receiver)
{
    if (!mailTemplateId || !items.empty())
        return;

    has_items = true;

    Loot mailLoot(NULL);


    mailLoot.FillLoot(mailTemplateId, LootTemplates_Mail, receiver, true, true);

    CharacterDatabase.BeginTransaction();
    CharacterDatabase.PExecute("UPDATE mail SET has_items = 1 WHERE id = %u", messageID);

    uint32 max_slot = mailLoot.GetMaxSlotInLootFor(receiver);
    for (uint32 i = 0; items.size() < MAX_MAIL_ITEMS && i < max_slot; ++i)
    {
        if (LootItem* lootitem = mailLoot.LootItemInSlot(i, receiver))
        {
            if (Item* item = Item::CreateItem(lootitem->itemid, lootitem->count, receiver))
            {
                item->SaveToDB();

                AddItem(item->GetGUIDLow(), item->GetEntry());

                receiver->AddMItem(item);

                CharacterDatabase.PExecute("INSERT INTO mail_items (mail_id,item_guid,item_template,receiver) VALUES ('%u', '%u', '%u','%u')",
                                           messageID, item->GetGUIDLow(), item->GetEntry(), receiver->GetGUIDLow());
            }
        }
    }

    CharacterDatabase.CommitTransaction();
}
