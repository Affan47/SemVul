qvariant_nameToType(const char* name)
{
    if (!name)
        return 0;

    if (strcmp(name, "QVariant") == 0)
        return 0xffffffff;
    if (strcmp(name, "QCString") == 0)
        return QMetaType::QByteArray;
    if (strcmp(name, "Q_LLONG") == 0)
        return QMetaType::LongLong;
    if (strcmp(name, "Q_ULLONG") == 0)
        return QMetaType::ULongLong;
    if (strcmp(name, "QIconSet") == 0)
        return QMetaType::QIcon;

    uint tp = QMetaType::type(name);
    return tp < QMetaType::User ? tp : 0;
}
