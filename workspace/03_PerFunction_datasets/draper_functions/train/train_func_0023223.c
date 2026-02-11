setMaxItems( int max )
{
    d->myMaximum = max;

    if (count() > d->myMaximum) {
        int oldCurrent = currentIndex();

        setDefaults();

        int offset = qMax (0, d->itemList.count() - d->myMaximum + d->defaultList.count());
        for ( int i = offset; i < d->itemList.count(); i++ )
            d->insertUrlItem( d->itemList[i] );

        if ( count() > 0 ) {
            if ( oldCurrent >= count() )
                oldCurrent = count() -1;
            setCurrentIndex( oldCurrent );
        }
    }
}
