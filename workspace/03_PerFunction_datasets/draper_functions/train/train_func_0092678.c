setFullScreen( QWidget* window, bool set )
{
  if( set )
    window->setWindowState( window->windowState() | Qt::WindowFullScreen );
  else
    window->setWindowState( window->windowState() & ~Qt::WindowFullScreen );
}
