DoUseEmberseerRunes(bool bReset)
{
    if (m_lEmberseerRunesGUIDList.empty())
    {
        return;
    }

    for (GuidList::const_iterator itr = m_lEmberseerRunesGUIDList.begin(); itr != m_lEmberseerRunesGUIDList.end(); ++itr)
    {
        if (bReset)
        {
            if (GameObject* pRune = instance->GetGameObject(*itr))
            {
                pRune->ResetDoorOrButton();
            }
        }
        else
        {
            DoUseDoorOrButton(*itr);
        }
    }
}
