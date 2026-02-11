PopulatePlugin(
    const QDomNode& pluginNode,
    CPluginInfo&    info)
{


    info.Clear();


    QDomNamedNodeMap pluginAttributes = pluginNode.attributes();

    info.SetName        ( pluginAttributes.namedItem( "name" ).nodeValue() );
    info.SetPlayerName  ( pluginAttributes.namedItem( "name" ).nodeValue() );
    info.SetId          ( pluginAttributes.namedItem( "id" ).nodeValue() );


    QString customPath = The::settings().pluginPlayerPath(info.GetId());
    if (customPath.size() != 0)
    {
        info.SetPlayerPath(customPath);
    }
    else
    {
        #ifdef WIN32

            string sPF = UnicornUtils::programFilesPath();
            if (sPF == "")
            {

                LOG(1, "Couldn't get PF path so trying to fake it.");
                sPF = "C:\\Program Files\\";
            }
            info.SetPlayerPath(QString::fromStdString(sPF) +
                               pluginNode.firstChildElement("Path").text() );
        #else

            info.SetPlayerPath( pluginNode.firstChildElement("Path").text() );
        #endif
    }

    info.SetDownloadURL  ( pluginNode.firstChildElement("Url").text() );
    info.SetVersion      ( pluginAttributes.namedItem( "version" ).nodeValue() );
    info.SetInstallDir   ( pluginNode.firstChildElement( "InstallDir" ).text() );
    info.SetPath         ( pluginNode.firstChildElement( "Path" ).text() );
    info.SetInstallArgs  ( pluginNode.firstChildElement( "Args" ).text() );
    info.SetPlayerVerMin ( pluginNode.firstChildElement( "MinVersion" ).text() );
    info.SetPlayerVerMax ( pluginNode.firstChildElement( "MaxVersion" ).text() );
    info.SetBootstrapType( pluginNode.firstChildElement( "Bootstrap" ).text() );
}
