lookupIconNameFor(const KUrl &url, KUriFilterData::UriTypes type)
{
    QString iconName;

    switch ( type )
    {
        case KUriFilterData::NetProtocol:
            iconName = KMimeType::favIconForUrl(url);
            if (iconName.isEmpty())
                iconName = KMimeType::iconNameForUrl( url );
            else
                iconName = KStandardDirs::locate("cache", iconName + QLatin1String(".png"));
            break;
        case KUriFilterData::LocalFile:
        case KUriFilterData::LocalDir:
        {
            iconName = KMimeType::iconNameForUrl( url );
            break;
        }
        case KUriFilterData::Executable:
        {
            QString exeName = url.path();
            exeName = exeName.mid( exeName.lastIndexOf( '/' ) + 1 );
            KService::Ptr service = KService::serviceByDesktopName( exeName );
            if (service && service->icon() != QLatin1String( "unknown" ))
                iconName = service->icon();


            else if ( !KIconLoader::global()->iconPath( exeName, KIconLoader::NoGroup, true ).isNull() )
                iconName = exeName;
            else

                iconName = QLatin1String("system-run");
            break;
        }
        case KUriFilterData::Help:
        {
            iconName = QLatin1String("khelpcenter");
            break;
        }
        case KUriFilterData::Shell:
        {
            iconName = QLatin1String("konsole");
            break;
        }
        case KUriFilterData::Error:
        case KUriFilterData::Blocked:
        {
            iconName = QLatin1String("error");
            break;
        }
        default:
            break;
    }

    return iconName;
}
