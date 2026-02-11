showScore (long score)
{
    if (m_scoreText)
        m_scoreText->setText (i18n("Score: %1", QString::number(score)
                                                .rightJustified(7, '0')));
}
