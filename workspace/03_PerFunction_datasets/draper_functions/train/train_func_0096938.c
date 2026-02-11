WriteSpellGoTargets(WorldPacket* data)
{


    *data << (uint8)(m_UniqueTargetInfo.size() + m_UniqueGOTargetInfo.size());

    for (TargetList::iterator ihit = m_UniqueTargetInfo.begin(); ihit != m_UniqueTargetInfo.end(); ++ihit)
    {
        *data << ihit->targetGUID;

        if (ihit->effectMask == 0)
        {

            ihit->missCondition = SPELL_MISS_IMMUNE2;
        }
        else if (ihit->missCondition == SPELL_MISS_NONE)
            { m_needAliveTargetMask |= ihit->effectMask; }
    }

    for (GOTargetList::const_iterator ighit = m_UniqueGOTargetInfo.begin(); ighit != m_UniqueGOTargetInfo.end(); ++ighit)
        { *data << ighit->targetGUID; }

    *data << uint8(0);


    if (!IsChanneledSpell(m_spellInfo))
        { m_needAliveTargetMask = 0; }
}
