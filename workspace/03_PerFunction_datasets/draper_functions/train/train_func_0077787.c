driveType() const
{
    QString type = m_device->prop("storage.drive_type").toString();

    if (type=="disk")
    {
        return Solid::StorageDrive::HardDisk;
    }
    else if (type=="cdrom")
    {
        return Solid::StorageDrive::CdromDrive;
    }
    else if (type=="floppy")
    {
        return Solid::StorageDrive::Floppy;
    }
    else if (type=="tape")
    {
        return Solid::StorageDrive::Tape;
    }
    else if (type=="compact_flash")
    {
        return Solid::StorageDrive::CompactFlash;
    }
    else if (type=="memory_stick")
    {
        return Solid::StorageDrive::MemoryStick;
    }
    else if (type=="smart_media")
    {
        return Solid::StorageDrive::SmartMedia;
    }
    else if (type=="sd_mmc")
    {
        return Solid::StorageDrive::SdMmc;
    }
    else
    {
        return Solid::StorageDrive::HardDisk;
    }
}
