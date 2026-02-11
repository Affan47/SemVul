postCoreInitialization()
{
    if (!user())
        return false;
    d->_model->checkUserPreferencesValidity();

    d->_model->emitUserConnected();

    Core::ICore::instance()->translators()->changeLanguage(settings()->value(Core::Constants::S_PREFERREDLANGUAGE, user()->value(Core::IUser::LanguageISO).toString()).toString());
    return true;
}
