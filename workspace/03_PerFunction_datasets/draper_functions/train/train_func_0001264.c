setCellRowAlignment( Symbol alignment ) {

    switch( alignment ) {
        case symbolEnd:     nextFormat.PgfCellAlignment = MifDoc::sBottom; break;
        case symbolCenter:  nextFormat.PgfCellAlignment = MifDoc::sMiddle; break;
        default:            nextFormat.PgfCellAlignment = MifDoc::sTop; break;
    }
}
