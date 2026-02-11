slotContextMenu(const QPoint& pos)
{

    if(!m_gameMenu)
    {
        m_mainMenu->exec(mapToGlobal(pos));
        return;
    }

    const Game* game = 0;
    emit queryActiveGame(&game);


    if(!game)
    {
        return;
    }
    QString link = anchorAt(pos);
    if(!link.isEmpty())
    {
        m_currentMove = link.section(':', 1).toInt();

        bool isVariation = !game->isMainline(m_currentMove);
        bool atLineStart = game->atLineStart(m_currentMove);
        bool atGameStart = m_currentMove == 0 || game->atGameStart(m_currentMove - 1);
        bool hasComment = !game->annotation(m_currentMove).isEmpty();
        bool hasPrecomment = !game->annotation(m_currentMove, Game::BeforeMove).isEmpty();
        bool hasNags = !game->nags().isEmpty();
        bool atLineEnd = game->atLineEnd(m_currentMove);

        m_startComment->setVisible(atLineStart && !hasPrecomment);
        m_addComment->setVisible(!hasComment);
        m_enumerateVariations1->setVisible(isVariation);
        m_enumerateVariations2->setVisible(isVariation);
        m_promoteVariation->setVisible(isVariation);
        m_removeVariation->setVisible(isVariation);
        m_VariationUp->setVisible(isVariation && game->canMoveVariationUp(m_currentMove));
        m_VariationDown->setVisible(isVariation && game->canMoveVariationDown(m_currentMove));
        m_removeNext->setVisible(!atLineEnd);
        m_removePrevious->setVisible(!atGameStart);
        m_removeNags->setVisible(hasNags);
        m_addNullMove->setVisible(atLineEnd);
        m_gameMenu->exec(mapToGlobal(pos));
    }
    else
    {
        m_browserMenu->exec(mapToGlobal(pos));
    }
}
