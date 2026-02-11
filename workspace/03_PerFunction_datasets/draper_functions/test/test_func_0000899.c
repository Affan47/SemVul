mayReturnContent(int cmd, const QString& protocol)
{
    if (cmd == CMD_GET)
        return true;

    if (cmd == CMD_MULTI_GET)
        return true;

    if (cmd == CMD_SPECIAL && protocol.startsWith(QLatin1String("http"), Qt::CaseInsensitive))
        return true;

    return false;
}
