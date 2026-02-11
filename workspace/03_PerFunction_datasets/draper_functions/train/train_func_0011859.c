gnc_lot_lookup (const GncGUID *guid, QofBook *book)
{
    QofCollection *col;
    if (!guid || !book) return NULL;
    col = qof_book_get_collection (book, GNC_ID_LOT);
    return (GNCLot *) qof_collection_lookup_entity (col, guid);
}
