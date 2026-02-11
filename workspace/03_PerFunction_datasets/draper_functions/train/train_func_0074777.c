getMainQuest()
{
	Quest * ret = _quests->getMainQuest();

	if( ! ret ) {
		ret = new Quest();
		_quests->setMainQuest( ret );
	}

	return ret;
}
