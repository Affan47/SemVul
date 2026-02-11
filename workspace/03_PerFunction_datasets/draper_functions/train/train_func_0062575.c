showStatus(const QString &msg) {
    QStringList args;
    args << msg;
    context->processCmd("showstatus", args);
}
