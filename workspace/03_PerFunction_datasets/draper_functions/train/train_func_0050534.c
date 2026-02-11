restoreEmpty()
{
    QString path(AppSettings->dataPath());

#ifdef Q_OS_WIN
    QString path1 = path + "/engines/uci";
    QString path2 = path + "/engines/winboard";
    restoreEmptyFromPath(path1, EngineData::UCI);
    restoreEmptyFromPath(path2, EngineData::WinBoard);
#endif

#ifdef Q_OS_MAC
    QString path1 = path + "/engines-mac/uci";
    QString path2 = path + "/engines-mac/winboard";
    restoreEmptyFromPath(path1, EngineData::UCI);
    restoreEmptyFromPath(path2, EngineData::WinBoard);
#endif

#ifdef Q_OS_LINUX
    QString path1 = path + "/engines-linux/uci";
    QString path2 = path + "/engines-linux/winboard";
    restoreEmptyFromPath(path1, EngineData::UCI);
    restoreEmptyFromPath(path2, EngineData::WinBoard);
#endif
}
