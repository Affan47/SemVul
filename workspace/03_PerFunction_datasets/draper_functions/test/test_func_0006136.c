menuListsPath(DefaultList rubrik) const
{
    QString tmp;
    switch (rubrik) {
        case ObservationDefaultList  : tmp = managerIni(DEFAULTLIST_RUB, DEFAULTLIST_OBS).toString(); break;
        case PrescriptionDefaultList : tmp = managerIni(DEFAULTLIST_RUB, DEFAULTLIST_PRE).toString(); break;
        case DocumentDefaultList     : tmp = managerIni(DEFAULTLIST_RUB, DEFAULTLIST_DOC).toString(); break;
        case ImageDefaultList        : tmp = managerIni(DEFAULTLIST_RUB, DEFAULTLIST_IMA).toString(); break;
    }
    if (!tmp.isEmpty())
        tmp.prepend(menuLibraryPath() + QDir::separator());
    return Utils::isDirExists(tmp);
}
