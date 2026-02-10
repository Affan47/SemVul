setGame(KReversiGame *game)
{


    if (m_game) {
        disconnect(m_game, SIGNAL(boardChanged()), this, SLOT(updateBoard()));
        disconnect(m_game, SIGNAL(moveFinished()), this, SLOT(gameMoveFinished()));
        disconnect(m_game, SIGNAL(gameOver()), this, SLOT(gameOver()));
        disconnect(m_game, SIGNAL(whitePlayerCantMove()), this, SLOT(whitePlayerCantMove()));
        disconnect(m_game, SIGNAL(blackPlayerCantMove()), this, SLOT(blackPlayerCantMove()));
        delete m_game;
    }

    m_game = game;

    if (m_game) {
        connect(m_game, SIGNAL(boardChanged()), this, SLOT(updateBoard()));
        connect(m_game, SIGNAL(moveFinished()), this, SLOT(gameMoveFinished()));
        connect(m_game, SIGNAL(gameOver()), this, SLOT(gameOver()));
        connect(m_game, SIGNAL(whitePlayerCantMove()), this, SLOT(whitePlayerCantMove()));
        connect(m_game, SIGNAL(blackPlayerCantMove()), this, SLOT(blackPlayerCantMove()));

        m_game->setDelay(m_delay);
    }

    m_hint = KReversiMove();

    updateBoard();
}
