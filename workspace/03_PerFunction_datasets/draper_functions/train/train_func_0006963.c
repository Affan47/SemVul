prettyName() const
{
    if (name().isEmpty()) return QObject::tr("(unknown)");
    return name();
}
