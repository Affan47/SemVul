resizeTo(QWidget* tl, int width, int height)
{
  KHTMLPart *part = qobject_cast<KHTMLPart*>(m_frame->m_part);
  if(!part)

    return;
  KParts::BrowserExtension *ext = part->browserExtension();
  if (!ext) {
    kDebug(6070) << "Window::resizeTo found no browserExtension";
    return;
  }


  if ( width < 100 || height < 100 ) {
    kDebug(6070) << "Window::resizeTo refused, window would be too small ("<<width<<","<<height<<")";
    return;
  }

  QRect sg = KGlobalSettings::desktopGeometry(tl);

  if ( width > sg.width() || height > sg.height() ) {
    kDebug(6070) << "Window::resizeTo refused, window would be too big ("<<width<<","<<height<<")";
    return;
  }

  kDebug(6070) << "resizing to " << width << "x" << height;

  emit ext->resizeTopLevelWidget( width, height );


  int right = tl->x() + tl->frameGeometry().width();
  int bottom = tl->y() + tl->frameGeometry().height();
  int moveByX = 0;
  int moveByY = 0;
  if ( right > sg.right() )
    moveByX = - right + sg.right();
  if ( bottom > sg.bottom() )
    moveByY = - bottom + sg.bottom();
  if ( moveByX || moveByY )
    emit ext->moveTopLevelWidget( tl->x() + moveByX , tl->y() + moveByY );
}
