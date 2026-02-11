IsUnderAttack(int square, Piece::Side s) {
	std::vector<Piece*>& playerPieces = (s == Piece::WHITE) ? whitePieces : blackPieces;
	std::vector<Piece*>& oppositePieces = (s == Piece::WHITE) ? blackPieces : whitePieces;

	size_t nPieces = oppositePieces.size();
	for(size_t i=0; i<nPieces; ++i) {
        if( oppositePieces[i]->GetSquare() == -1) continue;
	    if( oppositePieces[i]->Attacks(square, *this) ) return true;
	}
	return false;
}
