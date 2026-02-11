setIcon(const QString &icon)
{
    QDomNode metaDataNode = metaData(METADATA_FREEDESKTOP_OWNER, true);
    QDomElement iconElement = cd_or_create(metaDataNode, "bookmark:icon").toElement();
    iconElement.setAttribute ( "name", icon );


    if(!element.attribute("icon").isEmpty())
        element.removeAttribute("icon");
}
