rotateDown()
{

    if ( d->myIterateIndex == -1 )
        d->myText = currentText();

    --d->myIterateIndex;

    const QString currText = currentText();

    while ( d->myIterateIndex >= 0 &&
            (currText == itemText( d->myIterateIndex ) ||
             itemText( d->myIterateIndex ).isEmpty()) )
        --d->myIterateIndex;


    if ( d->myIterateIndex < 0 ) {
        if ( d->myRotated && d->myIterateIndex == -2 ) {
            d->myRotated = false;
            d->myIterateIndex = count() - 1;
            setEditText( itemText(d->myIterateIndex) );
        }
        else {
            if ( d->myIterateIndex == -2 ) {
                KNotification::event( "Textcompletion: No Match" ,
                                      i18n("No further items in the history."),
                                       QPixmap() , this, KNotification::DefaultEvent);
            }

            d->myIterateIndex = -1;
            if ( currentText() != d->myText )
                setEditText( d->myText );
        }
    } else {
        setCurrentIndex(d->myIterateIndex);
    }
}
