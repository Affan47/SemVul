resetStats()
{
	int gameIndex = indexToIdMap[ui->GameType->currentIndex()];
	Q_ASSERT(gameIndex >= 0);
	KConfigGroup cg(KGlobal::config(), scores_group);
	cg.writeEntry(QString("total%1").arg(gameIndex),0);
	cg.writeEntry(QString("won%1").arg(gameIndex),0);
	cg.writeEntry(QString("maxwinstreak%1").arg(gameIndex),0);
	cg.writeEntry(QString("maxloosestreak%1").arg(gameIndex),0);
	cg.writeEntry(QString("loosestreak%1").arg(gameIndex),0);
	cg.writeEntry(QString("winstreak%1").arg(gameIndex),0);
	cg.sync();

	setGameType(gameIndex);
}
