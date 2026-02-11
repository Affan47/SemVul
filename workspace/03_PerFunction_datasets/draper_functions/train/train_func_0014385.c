setDataToUi()
{
    ui->autoSave->setChecked(settings()->value(Core::Constants::S_ALWAYS_SAVE_WITHOUT_PROMPTING).toBool());
    ui->updateCheckingCombo->setCurrentIndex(settings()->value(Utils::Constants::S_CHECKUPDATE).toInt());
    ui->virtualDataCheck->setChecked(settings()->value(Core::Constants::S_ALLOW_VIRTUAL_DATA).toBool());
}
