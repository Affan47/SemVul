loadGame(int index, Game& game)
{
    if(!m_isOpen || index >= m_count)
    {
        return false;
    }
    lock();

    game.clear();
    loadGameHeaders(index, game);
    seekGame(index);
    skipTags();
    QString fen = m_index.tagValue(TagNameFEN, index);
    if(fen != "?")
    {
        game.setStartingBoard(fen);
    }
    parseMoves(&game);
    unlock();

    return m_variation != -1 || fen != "?";

}
