use12Clock() const
{
    if ((timeFormat().contains(QString::fromLatin1("%I")) > 0) ||
        (timeFormat().contains(QString::fromLatin1("%l")) > 0)) {
        return true;
    } else {
        return false;
    }
}
