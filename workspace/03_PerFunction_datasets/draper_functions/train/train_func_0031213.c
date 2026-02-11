onScriptDialogTriggered()
{
    ScriptWriterDialog dlg(Core::ICore::instance()->mainWindow());
    dlg.initialize();
    dlg.exec();
}
