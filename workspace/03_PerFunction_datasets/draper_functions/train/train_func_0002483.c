GetDefaultStateFlags(FactionEntry const* factionEntry) const
{
    if (!factionEntry)
        return 0;

    uint32 raceMask = m_player->getRaceMask();
    uint32 classMask = m_player->getClassMask();

    int idx = factionEntry->GetIndexFitTo(raceMask, classMask);

    return idx >= 0 ? factionEntry->ReputationFlags[idx] : 0;
}
