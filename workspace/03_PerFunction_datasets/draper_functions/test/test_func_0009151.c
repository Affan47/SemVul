errors()
{
    QStringList r;
    foreach(const LogData &v, m_Messages)
        if (v.isError())
            r << v.toString();
    return r;
}
