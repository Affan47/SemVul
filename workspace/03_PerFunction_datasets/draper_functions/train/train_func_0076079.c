languageChanged()
{

    _mode->setDisplayName(spec()->label());
    QString icon = spec()->iconFileName();
    icon.replace(Core::Constants::TAG_APPLICATION_THEME_PATH, settings()->path(Core::ISettings::BigPixmapPath));
    _mode->setIcon(QIcon(icon));
    _mode->setPriority(spec()->value(Form::FormItemSpec::Spec_Priority).toInt());

}
