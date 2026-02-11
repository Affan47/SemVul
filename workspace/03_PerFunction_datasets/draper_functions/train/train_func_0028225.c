keyPressEvent(QKeyEvent *e)
{
    if (d->bColorPicking) {
        if (e->key() == Qt::Key_Escape) {
            d->bColorPicking = false;
#ifdef Q_WS_X11
            kapp->removeX11EventFilter(d->filter);
            delete d->filter; d->filter = 0;
#endif
            releaseMouse();
            releaseKeyboard();
        }
        e->accept();
        return;
    }
    KDialog::keyPressEvent(e);
}
