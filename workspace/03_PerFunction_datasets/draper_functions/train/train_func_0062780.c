RemoveReporter(TestReporter* reporter)
{
    for (int index = 0; index < m_reporterCount; ++index)
    {
        if (m_reporters[index] == reporter)
        {
            m_reporters[index] = m_reporters[m_reporterCount - 1];
			--m_reporterCount;
			return true;
        }
    }

    return false;
}
