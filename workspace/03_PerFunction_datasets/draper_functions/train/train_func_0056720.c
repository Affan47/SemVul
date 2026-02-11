drawBackground( QPainter* painter, const QRectF& rect )
{
    switch ( m_backgroundType ) {
        case Settings::EnumBgType::theme: {


            static QByteArray theme_pre( m_renderer.theme()->identifier() );
            static QSize size_pre( rect.toRect().size() );
            static QPixmap pix( m_renderer.spritePixmap( QLatin1String( "BACKGROUND" ), size_pre ) );
            QSize size_offset = size_pre - rect.toRect().size();
            if ( size_offset.width() < -100 || size_offset.height() < -100 || theme_pre != m_renderer.theme()->identifier() ) {
                qWarning() << "export";
                theme_pre = m_renderer.theme()->identifier();
                size_pre = rect.toRect().size();
                pix = m_renderer.spritePixmap( QLatin1String( "BACKGROUND" ), size_pre );
                painter->drawPixmap( rect.topLeft(), pix );
            }
            else {
                painter->drawPixmap( rect.topLeft(), pix.scaled( rect.toRect().size() ) );
            }
            break;
        }
        case 3:
        case Settings::EnumBgType::color: {
            painter->fillRect( rect, Settings::bgColor() );
            break;
        }
        case 4:
        case Settings::EnumBgType::image: {

            static QString img_filepath( Settings::bgImage().path() );
            static QImage img( img_filepath );
            if ( img_filepath != Settings::bgImage().path() ) {
                img_filepath = Settings::bgImage().path();
                img = QImage( img_filepath );
            }
            if ( !img.isNull() )
                painter->drawImage( rect, img );
            else
                qWarning() << "Null background image " << Settings::bgImage();
            break;
        }
        default: {

            break;
        }
    }
}
