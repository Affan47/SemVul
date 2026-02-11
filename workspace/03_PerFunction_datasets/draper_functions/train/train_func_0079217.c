GetInstallPath()
{


    int nIdx = msPath.lastIndexOf("/");
    Q_ASSERT(nIdx != -1);

    QString sPath = msPath.mid( 0, nIdx + 1 );

    return sPath;

}
