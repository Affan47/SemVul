setItems( const QStringList& items )
{
    bool block = signalsBlocked();
    blockSignals( true );

    int rowIndex = 0;

    if (!count()) {
        addItems(items);
    } else {


        bool dirty = false;

        QStringList::ConstIterator it = items.constBegin();
        const QStringList::ConstIterator itEnd = items.constEnd();

        for ( ; it != itEnd; ++it) {
            if ( rowIndex < count() ) {
                const bool changed = ((KCompletionBoxItem*)item(rowIndex))->reuse( *it );
                dirty = dirty || changed;
            } else {
                dirty = true;

                addItem(*it);
            }
            rowIndex++;
        }


        if (rowIndex < count()) {
            dirty = true;
        }


        for ( ; rowIndex < count() ; ) {
            QListWidgetItem* item = takeItem(rowIndex);
            Q_ASSERT(item);
            delete item;
        }


    }

    if (isVisible() && size().height() != sizeHint().height())
        sizeAndPosition();

    blockSignals(block);
}
