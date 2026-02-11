rectToStr( const QRect &rect )
{
    return QString( "[(%1, %2), %3x%4]" )
           .arg( rect.x() )
           .arg( rect.y() )
           .arg( rect.width() )
           .arg( rect.height() );
}
