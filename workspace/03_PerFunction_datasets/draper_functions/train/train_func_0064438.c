setReadyState(ReadyState state)
{

    if (m_readyState == state)
        return;


    updatePlayState();
}
