runClicked()
{
    if (!runOrStopClicked())
    {
        ui.runButton->setText("Run");
        return;
    }
    if (ui.filename->text().isEmpty())
    {
        QMessageBox::warning(this, "tapemap", "Please specify tape file to process",
                QMessageBox::Ok, QMessageBox::NoButton);
        return;
    }
    if (!QFile::exists(ui.filename->text()))
    {
        QMessageBox::warning(this, "tapemap", "The specified file does not exist",
                QMessageBox::Ok, QMessageBox::NoButton);
        return;
    }
    std::vector<std::string> parameters;

    parameters.push_back(ui.filename->text().toStdString());

    std::string command = "tapemap";

    execute(command, Preferences::getInstance().hercDir(), parameters);
    ui.runButton->setText("Stop");
}
