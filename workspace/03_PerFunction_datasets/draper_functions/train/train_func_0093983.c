slotFind()
{
    if ( document()->isEmpty() )
        return;

    if ( d->findDlg ) {
      KWindowSystem::activateWindow( d->findDlg->winId() );
    } else {
      d->findDlg = new KFindDialog(this);
      connect( d->findDlg, SIGNAL(okClicked()), this, SLOT(slotDoFind()) );
    }
    d->findDlg->show();
}
