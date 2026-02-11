IsVersionNewer()
{
    if (mVersionNewer == eUnknown)
    {
        QString sSubKey = GetId();
        QString sInstalledVer = GetRegVersion(sSubKey);

        CVersionNumber verInstalled(sInstalledVer.toStdString());
        CVersionNumber verNew(GetVersion().toStdString());

        LOG(3, GetName() << " plugin installed ver: " << sInstalledVer <<
            ", server ver: " << GetVersion() << "\n");

        mVersionNewer = verNew > verInstalled ? eTrue : eFalse;
    }

    return mVersionNewer == eTrue;
}
