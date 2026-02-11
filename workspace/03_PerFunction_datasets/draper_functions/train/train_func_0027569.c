setClearButtonShown(bool show)
{
    if (show) {
        if (d->clearButton) {
            return;
        }

        d->clearButton = new KLineEditButton(this);
        d->clearButton->setObjectName("KLineEditButton");
        d->clearButton->setCursor( Qt::ArrowCursor );
        d->clearButton->setToolTip( i18nc( "@action:button Clear current text in the line edit", "Clear text" ) );

        updateClearButtonIcon(text());
        updateClearButton();
        connect(this, SIGNAL(textChanged(QString)), this, SLOT(updateClearButtonIcon(QString)));
    } else {
        disconnect(this, SIGNAL(textChanged(QString)), this, SLOT(updateClearButtonIcon(QString)));
        delete d->clearButton;
        d->clearButton = 0;
        d->clickInClear = false;
        if (d->style) {
            d->style.data()->m_overlap = 0;
        }
    }
}
