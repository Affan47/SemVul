SetData(uint32 uiType, uint32 uiData)
{
    switch (uiType)
    {
        case TYPE_KELRIS:
            if (m_auiEncounter[0] != DONE && uiData == DONE)
            {
                m_auiEncounter[0] = uiData;
            }
            break;
        case TYPE_SHRINE:
            m_auiEncounter[1] = uiData;
            if (uiData == IN_PROGRESS)
            {
                m_uiSpawnMobsTimer[m_uiWaveCounter] = 3000;
                ++m_uiWaveCounter;
            }
            else if (uiData == DONE)
            {
                DoUseDoorOrButton(GO_PORTAL_DOOR);
            }
            break;
        case TYPE_STONE:
            if (m_auiEncounter[2] != DONE && uiData == DONE)
            {
                m_auiEncounter[2] = uiData;
            }
            break;

    }

    if (uiData == DONE)
    {
        OUT_SAVE_INST_DATA;

        std::ostringstream saveStream;

        saveStream << m_auiEncounter[0] << " " << m_auiEncounter[1] << " " << m_auiEncounter[2];

        m_strInstData = saveStream.str();
        SaveToDB();
        OUT_SAVE_INST_DATA_COMPLETE;
    }
}
