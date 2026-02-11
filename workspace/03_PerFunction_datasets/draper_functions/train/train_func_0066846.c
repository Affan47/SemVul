getVar(const QByteArray &key)
{
    QByteArray cmd = "GET ";
    cmd += escape(key);
    cmd += '\n';
    QByteArray reply;
    command(cmd, &reply);
    return reply;
}
