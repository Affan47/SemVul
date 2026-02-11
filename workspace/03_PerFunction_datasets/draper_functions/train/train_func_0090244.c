typeChanged(const QString& newValue)
{
    if (isFba(newValue.toStdString()))
        setFba(true);
    else
        setCkd(true);
}
