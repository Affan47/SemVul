InitTalentForLevel()
{
    UpdateFreeTalentPoints();

    Unit* owner = GetOwner();
    if (!owner || owner->GetTypeId() != TYPEID_PLAYER)
        return;

    if (!m_loading)
        ((Player*)owner)->SendTalentsInfoData(true);
}
