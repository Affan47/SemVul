allTypes() const
{
    QStringList list;
    for (int i = 0; types_indices[i] != -1; i += 2)
        list.append(QLatin1String(types_string + types_indices[i]));

    list.append(QString::fromLatin1("lib"));


    list.append(QString::fromLatin1("socket"));
    list.append(QString::fromLatin1("tmp"));
    list.append(QString::fromLatin1("cache"));

    list.append(QString::fromLatin1("include"));


    return list;
}
