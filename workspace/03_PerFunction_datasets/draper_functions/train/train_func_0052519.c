KHTMLPart( KHTMLView *view, QObject *parent, GUIProfile prof )
: KParts::ReadOnlyPart( parent )
{
    d = 0;
    KHTMLGlobal::registerPart( this );
    setComponentData( KHTMLGlobal::componentData(), false );
    assert( view );
    if (!view->part())
        view->setPart( this );
    init( view, prof );
}
