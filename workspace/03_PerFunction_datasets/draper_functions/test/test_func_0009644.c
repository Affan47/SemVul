gameOver(int time)
{
    stateChanged("playing", KXMLGUIClient::StateReverse);

    KScoreDialog ksdialog(KScoreDialog::Name, this);
    ksdialog.initFromDifficulty(Kg::difficulty(),  false);
    ksdialog.setConfigGroup(qMakePair(
        m_lastUsedDifficulty->key(),
        m_lastUsedDifficulty->title()
    ));
    KScoreDialog::FieldInfo scoreInfo;
    scoreInfo[KScoreDialog::Score].setNum(time);
    if (ksdialog.addScore(scoreInfo, KScoreDialog::AskName)) {
        ksdialog.exec();
    }
}
