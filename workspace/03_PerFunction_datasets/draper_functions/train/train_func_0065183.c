setOption(const QString& optionString)
{
    QStringList temp = optionString.split('=');
    return setOption(temp[0], temp[1]);
}
