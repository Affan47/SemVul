CrawlerCanMoveTo(int destination, Board& board) const {

    if( board.IsSide(side, destination) ) return false;

    return CrawlerAttacks(destination);
}
