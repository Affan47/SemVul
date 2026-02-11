sortCaseInsensitively( QStringList input )
{


    QMap<QString, QString> map;
    foreach (QString s, input)
        map.insert( s.toLower(), s );

    QStringList output;
    QMapIterator<QString, QString> i( map );
    while (i.hasNext())
        output += i.next().value();

    return output;
}
