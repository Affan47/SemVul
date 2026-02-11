processColumns() {

    MifDoc::Tbl &mifTbl = mifTable( *MifDoc::CurInstance );
    mifTbl.setTblNumColumns( 0 );
    mifTbl.setTblNumColumns( Columns.size() );
    mifTbl.TblColumnWidths.resize( 0 );
    mifTbl.TblColumnWidths.resize( Columns.size() );
    mifTbl.TblColumnWidthsAreSet();

    long totalNonproportionalWidth = 0L;
    double totalProportionalUnits = 0.0;
    for( size_t i = 0; i < Columns.size(); i++ ) {
        if( Columns[i].hasWidth ) {
            if( Columns[i].width.tableUnitFactor ) {
                totalProportionalUnits += Columns[i].width.tableUnitFactor;
            } else {
                mifTbl.TblColumnWidths[i]
                 = MifFOTBuilder::curInstance().computeLengthSpec( Columns[i].width );
                totalNonproportionalWidth += mifTbl.TblColumnWidths[i];
            }
        }
    }

    double proportionalUnit = 0.0;
    if( totalProportionalUnits )
        proportionalUnit
         = ( parentTable().tableWidth - totalNonproportionalWidth ) / totalProportionalUnits;

    for( size_t i = 0; i < Columns.size(); i++ ) {
        if( Columns[i].hasWidth ) {
            if( Columns[i].width.tableUnitFactor )
                mifTbl.TblColumnWidths[i]
                 = long(proportionalUnit * Columns[i].width.tableUnitFactor);
        } else
            mifTbl.TblColumnWidths[i] = long(proportionalUnit);
    }

    columnsProcessed = true;
}
