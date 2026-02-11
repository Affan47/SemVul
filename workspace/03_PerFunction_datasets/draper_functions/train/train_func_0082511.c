readSettings(QSettings* cfg)
{
	int skills = cfg->value(CFG_SKILL, BEGINNER).toInt();
	QMap<int, QRadioButton*>::iterator it;
	it = m_player_two.computer.skills.find(skills);
	if(it != m_player_two.computer.skills.end())
		it.value()->setChecked(true);
	else
		m_player_two.computer.skills[BEGINNER]->setChecked(true);
	slot_skills();

	int rules = cfg->value(CFG_RULES, ENGLISH).toInt();
	if(rules == ENGLISH)
		m_player_one.rule_english->setChecked(true);
	else
		m_player_one.rule_russian->setChecked(true);

	m_player_one.white->setChecked(cfg->value(CFG_WHITE, false).toBool());

	m_player_one.name->setText(cfg->value(CFG_PLAYER1,
				getenv("USER")).toString());
	m_cfg_player2 = cfg->value(CFG_PLAYER2, "Player2").toString();
}
