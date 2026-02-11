Done()
{
    CC_LOCKER_TRACK_P_MTX_LOCK(ParserCommon::s_ParserMutex)

    bool done =    m_PriorityHeaders.empty()
                && m_SystemPriorityHeaders.empty()
                && m_BatchParseFiles.empty()
                && m_PredefinedMacros.IsEmpty()
                && !m_NeedMarkFileAsLocal
                && m_PoolTask.empty()
                && m_Pool.Done();

    CC_LOCKER_TRACK_P_MTX_UNLOCK(ParserCommon::s_ParserMutex)

    return done;
}
