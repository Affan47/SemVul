requestEject(const QModelIndex &index)
{
    Solid::Device device = deviceForIndex(index);

    Solid::OpticalDrive *drive = device.parent().as<Solid::OpticalDrive>();

    if (drive!=0) {
        connect(drive, SIGNAL(ejectDone(Solid::ErrorType,QVariant,QString)),
                this, SLOT(_k_storageTeardownDone(Solid::ErrorType,QVariant)));

        drive->eject();
    } else {
        QString label = data(index, Qt::DisplayRole).toString().replace('&',"&&");
        QString message = i18n("The device '%1' is not a disk and cannot be ejected.", label);
        emit errorMessage(message);
    }
}
