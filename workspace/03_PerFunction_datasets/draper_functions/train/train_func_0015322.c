vendor() const
{
    if (!isDrive()) {
        Device drive(drivePath());
        return drive.prop("Vendor").toString();
    }

    return prop("Vendor").toString();
}
