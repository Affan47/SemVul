handleEndedGame(int score, int level, int time)
{

    QTime t = QTime(0, 0).addSecs(time);

    QString timeString = t.toString("HH:mm");

    const int ALL_LEVELS = -1;

    KScoreDialog::FieldInfo scoreInfo;
    scoreInfo[KScoreDialog::Score].setNum(score);
    scoreInfo[KScoreDialog::Custom1] = timeString;
    if (level == ALL_LEVELS) {
        scoreInfo[KScoreDialog::Level] = i18n("Game won!");
    } else {
        scoreInfo[KScoreDialog::Level].setNum(level);
    }

    QPointer<KScoreDialog> ksdialog =
            new KScoreDialog(KScoreDialog::Name | KScoreDialog::Level, this);
    ksdialog->addField(KScoreDialog::Custom1, i18n("Time (hh:mm)"), "moves");
    ksdialog->addScore(scoreInfo);
    ksdialog->exec();

    if ( ksdialog ) {
        gameEngine->start("default");
        delete ksdialog;
    }
}
