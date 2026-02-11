setTopWidget( QWidget *topWidget )
{
    if( !topWidget )
      return;


    if ( !topWidget->inherits("KMainWindow") ) {
        topWidget->setWindowTitle(KGlobal::caption());
    }

#ifdef Q_WS_X11

    KStartupInfo::setWindowStartupId(topWidget->winId(), startupId());
#endif
}
