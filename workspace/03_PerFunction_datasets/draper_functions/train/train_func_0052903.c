Roll(bool rate) const
{
    if (chance >= 100.0f)
        return true;

    if (mincountOrRef < 0)
        return roll_chance_f(chance * (rate ? sWorld.getConfig(CONFIG_FLOAT_RATE_DROP_ITEM_REFERENCED) : 1.0f));

    ItemPrototype const* pProto = ObjectMgr::GetItemPrototype(itemid);

    float qualityModifier = pProto && rate ? sWorld.getConfig(qualityToRate[pProto->Quality]) : 1.0f;

    return roll_chance_f(chance * qualityModifier);
}
