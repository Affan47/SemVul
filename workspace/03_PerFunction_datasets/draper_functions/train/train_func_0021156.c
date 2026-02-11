RestoreCharges()
{
    ItemPrototype const* itemProto = GetProto();

    for (int i = 0; i < MAX_ITEM_PROTO_SPELLS; ++i)
    {
        if (GetSpellCharges(i) != itemProto->Spells[i].SpellCharges)
        {
            SetSpellCharges(i, itemProto->Spells[i].SpellCharges);
            SetState(ITEM_CHANGED);
        }
    }
}
