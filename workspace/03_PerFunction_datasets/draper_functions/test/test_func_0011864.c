readFileContent(const QString absPath)
    {
        QString encoding;
        switch (settings()->value(Constants::S_DEFAULT_FILE_ENCODING).toInt()) {
        case Constants::AutoDetect:
            if (Utils::isRunningOnLinux() || Utils::isRunningOnFreebsd())
                encoding = "UTF-8";
            else if (Utils::isRunningOnMac())
                encoding = "MacRoman";
            else if (Utils::isRunningOnWin())
                encoding = "ISO-8859-1";
            break;
        case Constants::ForceUtf8: encoding = "UTF-8"; break;
        case Constants::ForceMacRoman: encoding = "MacRoman"; break;
        case Constants::ForceIso8859_1: encoding = "ISO-8859-1"; break;
        }
        return Utils::readTextFile(absPath, encoding);
    }
