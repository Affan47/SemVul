suspendMarquees()
{
    if (m_marquee)
        m_marquee->suspend();

    for (RenderLayer* curr = firstChild(); curr; curr = curr->nextSibling())
        curr->suspendMarquees();
}
