tabBarWidthForMaxChars( int maxLength )
{
  int hframe, overlap;
  hframe  = tabBar()->style()->pixelMetric( QStyle::PM_TabBarTabHSpace, 0L, tabBar() );
  overlap = tabBar()->style()->pixelMetric( QStyle::PM_TabBarTabOverlap, 0L, tabBar() );

  const QFontMetrics fm = tabBar()->fontMetrics();
  int x = 0;
  for ( int i = 0; i < count(); ++i ) {
    QString newTitle = d->m_tabNames.value( i );
    newTitle = KStringHandler::rsqueeze( newTitle, maxLength ).leftJustified( d->m_minLength, ' ' );

    int lw = fm.width( newTitle );
    int iw = 0;
    if ( !tabBar()->tabIcon( i ).isNull() ) {
      iw = tabBar()->tabIcon( i ).pixmap( style()->pixelMetric( QStyle::PM_SmallIconSize ), QIcon::Normal ).width() + 4;
    }
#ifndef KDE_NO_DEPRECATED
    if ( isCloseButtonEnabled() ) {

      iw += KIconLoader::SizeSmall * 3 / 2;
    }
#endif
    x += ( tabBar()->style()->sizeFromContents( QStyle::CT_TabBarTab, 0L,
         QSize( qMax( lw + hframe + iw, QApplication::globalStrut().width() ), 0 ),
         this ) ).width();
  }

  return x;
}
