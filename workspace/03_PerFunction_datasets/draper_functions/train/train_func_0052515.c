setTZ(const QByteArray &zoneName)
{
    QByteArray tz = zoneName;
    tz.prepend(":");
    bool setTZ = multiParse;
    if (!setTZ)
    {
        savedTZ = qgetenv("TZ");
        TZIsSaved = true;
        setTZ = (tz != savedTZ);
    }
    if (setTZ)
    {
        ::setenv("TZ", tz, 1);
        ::tzset();
    }
}
