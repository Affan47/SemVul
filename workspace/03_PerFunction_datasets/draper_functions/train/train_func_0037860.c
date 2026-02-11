ask_screenshot_to_server(QString to, QString from, QString file_name)
{
    identity->blocked = true;
    isScreenshot = true;
    controller->ask_file_to_server(to, from, file_name);
}
