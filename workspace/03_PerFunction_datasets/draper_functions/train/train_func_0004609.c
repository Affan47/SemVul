Part( QObject *parent )
    : QObject( parent ), PartBase( *new PartPrivate(this) )
{
    PartBase::setPartObject( this );
}
