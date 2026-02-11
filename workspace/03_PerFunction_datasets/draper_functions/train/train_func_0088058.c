readItem(const QMap<QString,QString> &properties)
{
    QString FileName, Title, Length;

    for (QMap<QString,QString>::ConstIterator i=properties.begin(); i!=properties.end(); ++i )
    {
        QString n = i.key();
        QString val = i.value();

        if ((n == "url") || (n == "file"))
        {
            FileName = val;
        }
        else if (n == "title")
        {
            Title = val;
        }
        else if (n == "length")
        {
            Length = val;
        }
    }

    PlayListEntry NewEntry(FileName, Title, Length);
    list.append(NewEntry);
}
