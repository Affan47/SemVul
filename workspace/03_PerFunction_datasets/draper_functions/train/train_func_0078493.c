setSvgFile( const QString &file )
{
    if( d->sharedRenderer )
    {
        if( !d->sharedRenderer->load( file ) )
            qWarning() << "Could not load SVG file " << file;
        else
        {
            d->file = file;

        }
    }
    else
        qWarning() << "No shared renderer!";
}
