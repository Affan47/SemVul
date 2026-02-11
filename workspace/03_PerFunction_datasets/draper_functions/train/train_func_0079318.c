isSquare(const vector<vector<pair<int, int> > > &matrixPreknowledge, unsigned row, unsigned col, unsigned subsquareLen){
    if((matrixPreknowledge[row][col].first>=subsquareLen && matrixPreknowledge[row][col].second>=subsquareLen) && (matrixPreknowledge[row][col+subsquareLen-1].second>=subsquareLen) && (matrixPreknowledge[row+subsquareLen-1][col].first>=subsquareLen))
	return true;
    return false;
}
