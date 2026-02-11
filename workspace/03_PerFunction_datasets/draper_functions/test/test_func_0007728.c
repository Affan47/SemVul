setIcon( const QString& file )
{
    QPixmap p( file );
    p = p.scaled( 32, 32, Qt::IgnoreAspectRatio, Qt::SmoothTransformation );
    ui.iconLabel->setPixmap( p );
}
