findMetadata(const QString & forOwner, QDomNode& parent, bool create)
{
    bool forOwnerIsKDE = forOwner == METADATA_KDE_OWNER;

    QDomElement metadataElement;
    for ( QDomNode _node = parent.firstChild(); !_node.isNull(); _node = _node.nextSibling() ) {
        QDomElement elem = _node.toElement();
        if ( !elem.isNull() && elem.tagName() == "metadata" ) {
            const QString owner = elem.attribute( "owner" );
            if ( owner == forOwner )
                return elem;
            if ( owner.isEmpty() && forOwnerIsKDE )
                metadataElement = elem;
        }
    }
    if ( create && metadataElement.isNull() ) {
        metadataElement = parent.ownerDocument().createElement( "metadata" );
        parent.appendChild(metadataElement);
        metadataElement.setAttribute( "owner", forOwner );

    } else if (!metadataElement.isNull() && forOwnerIsKDE) {

        metadataElement.setAttribute( "owner", METADATA_KDE_OWNER );
    }
    return metadataElement;
}
