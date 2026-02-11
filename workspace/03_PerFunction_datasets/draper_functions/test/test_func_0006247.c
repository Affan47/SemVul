contextMenuEvent(QContextMenuEvent* ev)
{


    const bool squeezed = text() != d->fullText;
    const bool showCustomPopup = squeezed;
    if (showCustomPopup) {
        QMenu menu(this);

        KAction* act = new KAction(i18n("&Copy Full Text"), &menu);
        connect(act, SIGNAL(triggered()), this, SLOT(_k_copyFullText()));
        menu.addAction(act);

        ev->accept();
        menu.exec(ev->globalPos());
    } else {
        QLabel::contextMenuEvent(ev);
    }
}
