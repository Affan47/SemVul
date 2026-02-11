writeDefaultSettings(Core::ISettings *s)
{

    Utils::Log::addMessage("ApplicationGeneralPreferencesWidget", tkTr(Trans::Constants::CREATING_DEFAULT_SETTINGS_FOR_1).arg("FreeDiamsMainWindow"));
    s->setValue(Core::Constants::S_ALWAYS_SAVE_WITHOUT_PROMPTING, true);
    s->setValue(Utils::Constants::S_CHECKUPDATE, Trans::Constants::CheckUpdate_AtStartup);
    s->setValue(Core::Constants::S_ALLOW_VIRTUAL_DATA, true);

    s->sync();
}
