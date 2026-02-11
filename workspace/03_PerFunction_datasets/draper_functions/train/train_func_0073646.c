GetTime()
{

    if (m_dPauseTime != -1.)
	return m_dPauseTime;

    double actual_time = avm_get_time_diff(avm_get_time_us(), m_llTimeStart)
        + m_dAudioRealpos - m_fAsync;


    return (actual_time > 0.) ? actual_time : 0.;
}
