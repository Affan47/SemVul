traverseNeighbors( int x, int y, int color, bool (GameScene::*func)(Piece*) )
{
    if ( x < 0 || x >= PWC || y < 0 || y >= PHC )
        return;

    int index = y * PWC + x;
    if ( m_pieces[index]->m_color == color ) {
        if ( (this->*func)( m_pieces[index] ) ) {
            traverseNeighbors( x-1, y, color, func );
            traverseNeighbors( x, y-1, color, func );
            traverseNeighbors( x+1, y, color, func );
            traverseNeighbors( x, y+1, color, func );
        }
    }
}
