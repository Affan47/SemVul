decode_start()
{
    init_frame();

    if (m_progressive_flag)
        init_progressive();
    else
        init_sequential();
}
