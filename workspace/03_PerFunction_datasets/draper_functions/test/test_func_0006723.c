initialize(const QStringList &arguments, QString *errorString)
{
    if (Utils::Log::warnPluginsCreation())
        qWarning() << "TextEditorPlugin::initialize";
    Q_UNUSED(arguments);
    Q_UNUSED(errorString);


    Core::ICore::instance()->translators()->addNewTranslator("plugin_texteditor");

    return true;
}
