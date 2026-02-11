loadResource(String &url)
{
    KUrl kurl(url.string());
    if (!m_player)
        return;
    if (autoplay())
        m_player->play(kurl);
    else
        m_player->load(kurl);
}
