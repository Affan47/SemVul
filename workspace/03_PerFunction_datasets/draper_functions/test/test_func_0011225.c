changeStatus() {
	updateStatusbar();

	if (Settings::gameType() == Settings::EnumGameType::Snake)
	{
		KScoreDialog scoreDialog(KScoreDialog::Score | KScoreDialog::Name, this);
		scoreDialog.initFromDifficulty(Kg::difficulty());

		KScoreDialog::FieldInfo scoreInfo;
		scoreInfo[KScoreDialog::Name] = m_tron->getPlayer(0)->getName();
		scoreInfo[KScoreDialog::Score].setNum(m_tron->getPlayer(0)->getScore());
		if (scoreDialog.addScore(scoreInfo) != 0)
			scoreDialog.exec();
	}
}
