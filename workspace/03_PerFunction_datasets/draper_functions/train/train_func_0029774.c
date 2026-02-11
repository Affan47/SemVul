slotAutoPlayTimeout()
{
    if(m_autoAnalysis->isChecked() && m_mainAnalysis->isEngineRunning() && (m_AutoInsertLastBoard != m_boardView->board()))
    {
        Analysis a = m_mainAnalysis->getMainLine();
        if(!a.variation().isEmpty())
        {
            Move m = a.variation().first();
            if(!game().currentNodeHasMove(m.from(), m.to()))
            {
                if(!game().isEcoPosition())
                {
                    slotGameAddVariation(a);
                }
            }
        }
        m_AutoInsertLastBoard = m_boardView->board();
    }
    if(game().atGameEnd() && AppSettings->getValue("/Board/AutoSaveAndContinue").toBool())
    {
        saveGame();
        loadNextGame();
    }
    else
    {
        slotGameMoveNext();
    }
    m_autoPlayTimer->start();
}
