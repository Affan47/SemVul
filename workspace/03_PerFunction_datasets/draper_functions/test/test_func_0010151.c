normalizeRows() {

  size_t maxCellsInRow = Columns.size()+1;
  Vector<Row> *rows;
  for( int step = 0; step < 2; step++ ) {
    for( int rowType = 0; rowType < 3; rowType++ ) {
      switch( rowType ) {
        case 0: rows = &Header; break;
        case 1: rows = &Body; break;
        default: rows = &Footer;
      }
      for( size_t r = 0; r < rows->size(); r++ ) {
        if( step == 0 ) {
          if( (*rows)[r].Cells.size() > 1 ) {
            size_t lastCellIdx = (*rows)[r].Cells.size()-2;
            Cell &lastCell = (*rows)[r].Cells[lastCellIdx];
            if( !lastCell.missing
                  &&
                lastCellIdx+lastCell.nColumnsSpanned+1 > maxCellsInRow )
              maxCellsInRow = lastCellIdx+lastCell.nColumnsSpanned+1;
          }
        } else if( (*rows)[r].Cells.size() < maxCellsInRow )
          (*rows)[r].Cells.resize( maxCellsInRow );
      }
    }
  }
}
