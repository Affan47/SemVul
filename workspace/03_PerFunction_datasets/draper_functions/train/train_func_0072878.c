iconName() const
{
#if !defined(KDE_NO_WARNING_OUTPUT)
    if (!(d->info->passedProperties()[ NETWinInfo::PROTOCOLS ] & NET::WMIconName))
        kWarning(176) << "Pass NET::WMIconName to KWindowInfo";
#endif
    if( d->info->iconName() && d->info->iconName()[ 0 ] != '\0' )
        return QString::fromUtf8( d->info->iconName());
    if( !d->iconic_name_.isEmpty())
        return d->iconic_name_;
    return name();
}
