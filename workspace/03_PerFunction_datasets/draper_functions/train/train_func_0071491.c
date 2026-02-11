readSettings(QSettings *settings)
{
    bool conv_ok;

    rc_freq = settings->value("input/frequency", 144500000).toLongLong(&conv_ok);
    rc_filter_offset = settings->value("receiver/offset", 0).toInt(&conv_ok);


    rc_port = settings->value("remote_control/port", 7356).toInt(&conv_ok);
    if (rc_server.isListening())
    {
        rc_server.close();
        rc_server.listen(QHostAddress::Any, rc_port);
    }


    if (settings->contains("remote_control/allowed_hosts"))
        rc_allowed_hosts = settings->value("remote_control/allowed_hosts").toStringList();
}
