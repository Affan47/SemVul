getOwnPropertySlot( KJS::ExecState *exec, const KJS::Identifier &propertyName, KJS::PropertySlot &slot )
{

    QObject *obj = object<QObject>();
    const QMetaObject *meta = obj->metaObject();
    int propIndex = meta->indexOfProperty( propertyName.ascii() );
    if ( propIndex != -1 ) {
        if(! validProperty(meta->property(propIndex), m_access))
            return false;

        slot.setCustom( this, propertyGetter );
        return true;
    }
    return ObjectBinding::getOwnPropertySlot( exec, propertyName, slot );
}
