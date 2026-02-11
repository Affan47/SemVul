load(const QString &file) {
    kDebug() << "Layout loading";

    QString layoutPath;
    kDebug() << "Attempting to load .desktop at" << file;


    QFile bgfile(file);
    if (!bgfile.open(QIODevice::ReadOnly)) {
      return (false);
    }
    bgfile.close();

    KConfig bgconfig(file, KConfig::SimpleConfig);
    KConfigGroup group = bgconfig.group("KMahjonggLayout");

    d->authorproperties.insert("Name", group.readEntry("Name"));
    d->authorproperties.insert("Author", group.readEntry("Author"));
    d->authorproperties.insert("Description", group.readEntry("Description"));
    d->authorproperties.insert("AuthorEmail", group.readEntry("AuthorEmail"));


    int bgversion = group.readEntry("VersionFormat",0);

    if (bgversion > kLayoutVersionFormat) {
        return false;
    }

    QString layoutName = group.readEntry("FileName");

    layoutPath = KStandardDirs::locate("kmahjongglayout", layoutName);
    kDebug() << "Using layout at" << layoutPath;
    d->filename = layoutPath;

    if (layoutPath.isEmpty()) return (false);

    if (!d->board->loadBoardLayout(d->filename)) return (false);

    filename = file;

   return true;
}
