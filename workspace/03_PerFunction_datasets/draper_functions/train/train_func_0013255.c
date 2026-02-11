loadDefault()
{
    QString idx = "default.desktop";

    QString layoutPath = KStandardDirs::locate("kmahjongglayout", idx);
    kDebug() << "Inside LoadDefault(), located layout at" << layoutPath;
    if (layoutPath.isEmpty()) {
		return false;
    }
    return load(layoutPath);
}
