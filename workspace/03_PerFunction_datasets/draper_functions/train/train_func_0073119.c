execute()
{
    if (commandLineEdit->text() != "") {

        emit sendCommand(commandLineEdit->text(), remote_path);
        save_command(commandLineEdit->text());
        commandLineEdit->setText("");
    }
}
