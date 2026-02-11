loadDialogData()
{

    address->setText(AppSettings::proxyAddress());
    port->setValue(AppSettings::proxyPort());
    directConnection->setChecked(AppSettings::isDirectConnection());
    proxyWidget->setDisabled(directConnection->isChecked());
}
