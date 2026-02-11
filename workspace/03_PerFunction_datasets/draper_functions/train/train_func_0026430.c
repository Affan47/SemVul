isChanged(const char *type)
{
    return self()->d->changeList.contains(QString::fromLatin1(type));
}
