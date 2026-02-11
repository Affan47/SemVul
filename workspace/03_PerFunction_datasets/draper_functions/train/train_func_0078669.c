UnpicklePrologue(void)
{
    m_startTable.resize(kPickleNumStates);
    m_endTable.resize(kPickleNumStates);

    m_startTable[kPickleInit]["records"] = &GameRecords::HandleRecordsStart;
    m_startTable[kPickleData]["splittime"] = &GameRecords::NullHandler;
    m_endTable[kPickleData]["splittime"] = &GameRecords::HandleSplitTimeEnd;
    m_startTable[kPickleData]["laptime"] = &GameRecords::NullHandler;
    m_endTable[kPickleData]["laptime"] = &GameRecords::HandleLapTimeEnd;
    m_startTable[kPickleData]["racetime"] = &GameRecords::NullHandler;
    m_endTable[kPickleData]["racetime"] = &GameRecords::HandleRaceTimeEnd;
    m_startTable[kPickleData]["checksum"] = &GameRecords::NullHandler;
    m_endTable[kPickleData]["checksum"] = &GameRecords::NullHandler;
    m_endTable[kPickleData]["records"] = &GameRecords::HandleRecordsEnd;
    m_pickleState=kPickleInit;
    Reset();
}
