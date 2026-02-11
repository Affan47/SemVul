updateInformationForVersion(const QList<GenericUpdateInformation> &list, const QString &version)
{
    Utils::VersionNumber v(version);
    return updateInformationForVersion(list, v);
}
