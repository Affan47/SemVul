VersionMatch()
{

    QString sExeVer = GetExeVersion(msPlayerPath);

    if (sExeVer == "")
    {

        LOG(1, "Couldn't read version number for " << msPlayerName << "\n");


        bool bVersionRestricted = msPlayerVerMin != "" || msPlayerVerMax != "";

        LOG(1, "Version restricted: " << (bVersionRestricted ? "yes" : "no") <<
            ", assuming match: " << (!bVersionRestricted ? "yes" : "no") << "\n");

        return !bVersionRestricted;
    }


    LOG(3, "Player version to test: " << msPlayerVerMin << " - " << msPlayerVerMax << "\n");
    LOG(3, "Version of " << msPlayerName << ": " << sExeVer << "\n");


    CVersionNumber fileVer(sExeVer.toStdString());
    CVersionNumber minVer(msPlayerVerMin.toStdString());


    QString sMaxVer = msPlayerVerMax;
    if (sMaxVer == "")
    {
        sMaxVer = QString("%1.%2.%3.%4").arg(INT_MAX).arg(INT_MAX).arg(INT_MAX).arg(INT_MAX);
    }

    CVersionNumber maxVer(sMaxVer.toStdString());


    return (fileVer >= minVer && fileVer <= maxVer);
}
