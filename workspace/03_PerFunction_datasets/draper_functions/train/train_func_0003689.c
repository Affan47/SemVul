insertSpanCell( RenderTableCell *cell )
{
    if ( !cell || cell == (RenderTableCell *)-1 || cell->colSpan() == 1 )
	return;


    int size = spanCells.size();
    if ( !size || spanCells[size-1] != 0 ) {
	spanCells.resize( size + 10 );
	for ( int i = 0; i < 10; i++ )
	    spanCells[size+i] = 0;
	size += 10;
    }


    int pos = 0;
    int span = cell->colSpan();
    while ( pos < spanCells.size() && spanCells[pos] && span > spanCells[pos]->colSpan() )
	pos++;
    memmove( spanCells.data()+pos+1, spanCells.data()+pos, (size-pos-1)*sizeof( RenderTableCell * ) );
    spanCells[pos] = cell;
}
