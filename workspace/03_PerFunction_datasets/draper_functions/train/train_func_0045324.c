update()
{
    moveLabel->setText(QString::number(m_game->currentMoveNumber()));

    if (m_game->moves().size() > 0) {
        Move last = m_game->lastMove();
        if (last.player()->isWhite()) {
            lastMoveLabel->setText(i18nc("Indication who played the last move", "%1 (white)", last.stone().toString()));
        } else if (last.player()->isBlack()) {
            lastMoveLabel->setText(i18nc("Indication who played the last move", "%1 (black)", last.stone().toString()));
        } else {
            lastMoveLabel->clear();
        }
    }

    if (m_game->currentPlayer().isWhite()) {
        QPixmap whiteStone = ThemeRenderer::self()->renderElement(Kigo::ThemeRenderer::WhiteStone, QSize(64, 64));
        currentPlayerImageLabel->setPixmap(whiteStone);
        currentPlayerLabel->setText(i18n("White's turn"));
    } else if (m_game->currentPlayer().isBlack()) {
        QPixmap blackStone = ThemeRenderer::self()->renderElement(Kigo::ThemeRenderer::BlackStone, QSize(64, 64));
        currentPlayerImageLabel->setPixmap(blackStone);
        currentPlayerLabel->setText(i18n("Black's turn"));
    } else {
        currentPlayerLabel->clear();
    }

    whiteCapturesLabel->setText(i18np("%1 capture", "%1 captures", m_game->captures(m_game->whitePlayer())));
    blackCapturesLabel->setText(i18np("%1 capture", "%1 captures", m_game->captures(m_game->blackPlayer())));
}
