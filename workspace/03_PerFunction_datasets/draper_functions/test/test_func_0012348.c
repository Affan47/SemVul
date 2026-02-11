SendActionMenu_npc_prof_leather(Player* pPlayer, Creature* pCreature, uint32 uiAction)
{
    switch (uiAction)
    {
        case GOSSIP_ACTION_TRADE:
            pPlayer->SEND_VENDORLIST(pCreature->GetObjectGuid());
            break;
        case GOSSIP_ACTION_TRAIN:
            pPlayer->SEND_TRAINERLIST(pCreature->GetObjectGuid());
            break;

        case GOSSIP_ACTION_INFO_DEF + 1:
            if (EquippedOk(pPlayer, S_UNLEARN_DRAGON))
            {
                if (pPlayer->GetMoney() >= uint32(GetUnlearnCostMedium(pPlayer)))
                {
                    pPlayer->CastSpell(pPlayer, S_UNLEARN_DRAGON, true);
                    ProfessionUnlearnSpells(pPlayer, S_UNLEARN_DRAGON);
                    pPlayer->ModifyMoney(-GetUnlearnCostMedium(pPlayer));
                }
                else
                {
                    pPlayer->SendBuyError(BUY_ERR_NOT_ENOUGHT_MONEY, pCreature, 0, 0);
                }
            }
            else
            {
                pPlayer->SendEquipError(EQUIP_ERR_CANT_DO_RIGHT_NOW, NULL, NULL);
            }
            pPlayer->CLOSE_GOSSIP_MENU();
            break;
        case GOSSIP_ACTION_INFO_DEF + 2:
            if (EquippedOk(pPlayer, S_UNLEARN_ELEMENTAL))
            {
                if (pPlayer->GetMoney() >= uint32(GetUnlearnCostMedium(pPlayer)))
                {
                    pPlayer->CastSpell(pPlayer, S_UNLEARN_ELEMENTAL, true);
                    ProfessionUnlearnSpells(pPlayer, S_UNLEARN_ELEMENTAL);
                    pPlayer->ModifyMoney(-GetUnlearnCostMedium(pPlayer));
                }
                else
                {
                    pPlayer->SendBuyError(BUY_ERR_NOT_ENOUGHT_MONEY, pCreature, 0, 0);
                }
            }
            else
            {
                pPlayer->SendEquipError(EQUIP_ERR_CANT_DO_RIGHT_NOW, NULL, NULL);
            }
            pPlayer->CLOSE_GOSSIP_MENU();
            break;
        case GOSSIP_ACTION_INFO_DEF + 3:
            if (EquippedOk(pPlayer, S_UNLEARN_TRIBAL))
            {
                if (pPlayer->GetMoney() >= uint32(GetUnlearnCostMedium(pPlayer)))
                {
                    pPlayer->CastSpell(pPlayer, S_UNLEARN_TRIBAL, true);
                    ProfessionUnlearnSpells(pPlayer, S_UNLEARN_TRIBAL);
                    pPlayer->ModifyMoney(-GetUnlearnCostMedium(pPlayer));
                }
                else
                {
                    pPlayer->SendBuyError(BUY_ERR_NOT_ENOUGHT_MONEY, pCreature, 0, 0);
                }
            }
            else
            {
                pPlayer->SendEquipError(EQUIP_ERR_CANT_DO_RIGHT_NOW, NULL, NULL);
            }
            pPlayer->CLOSE_GOSSIP_MENU();
            break;
    }
}
