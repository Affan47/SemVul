openRideFile(QFile &file, QStringList &errors, QList<RideFile*>*) const
{
    (void) errors;
    RideFile *rideFile = new RideFile();
    rideFile->setDeviceType("Sigma ROX Memory");
    rideFile->setFileFormat("Sigma Memory File (smf)");

    SmfParser handler(rideFile);

    QXmlInputSource source (&file);
    QXmlSimpleReader reader;
    reader.setContentHandler (&handler);
    reader.parse (source);

    return rideFile;
}
