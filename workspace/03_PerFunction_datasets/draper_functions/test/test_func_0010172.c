setMood()
{
	QString moodstr = ui_.cb_type->currentText();
	if (moodstr == tr("<unset>")) {
		pa_->pepManager()->retract("http://jabber.org/protocol/mood", "current");
	} else {
		Mood::Type type = MoodCatalog::instance()->findEntryByText(moodstr).type();
		pa_->pepManager()->publish("http://jabber.org/protocol/mood", PubSubItem("current",Mood(type,ui_.le_text->text()).toXml(*pa_->client()->rootTask()->doc())), PEPManager::PresenceAccess);
	}
	close();
}
