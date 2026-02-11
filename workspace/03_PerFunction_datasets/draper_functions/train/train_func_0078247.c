setDataToUi()
{
    Core::ISettings *s = settings();
    hideLabCheck->setChecked(s->value(DrugsDB::Constants::S_HIDELABORATORY).toBool());
    ALDBefore->textEdit()->setHtml(s->value(DrugsDB::Constants::S_ALD_PRE_HTML).toString());
    ALDAfter->textEdit()->setHtml(s->value(DrugsDB::Constants::S_ALD_POST_HTML).toString());
}
