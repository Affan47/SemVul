setCurrentItem(const QString &filename )
{
    if (!filename.isNull()) {
        KFileItem item;
        for ( (item = firstFileItem()); !item.isNull(); item = nextItem( item ) ) {
            if (item.name() == filename) {
                setCurrentItem( item );
                return;
            }
        }
    }

    kDebug(kfile_area) << "setCurrentItem: no match found: " << filename;
}
