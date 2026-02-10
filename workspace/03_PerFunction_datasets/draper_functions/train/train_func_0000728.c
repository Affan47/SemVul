initializeStorage(int matrixSize){
    return MAXSUMSTORAGE(matrixSize, vector<vector<vector<int> > > (matrixSize, vector<vector<int> > (matrixSize, vector<int>(matrixSize, 0))));
}
