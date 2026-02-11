Problem_7_test(){
    Chapter1 chapter1;
    MATRIX matrix, matrixCorrect;

    chapter1.Problem_7(matrix);
    if(!matrix.empty())
	return false;


    int temp[3]={1,2,0};
    matrix.push_back(vector<int>(temp, temp+3));
    matrix.push_back(vector<int>(temp, temp+3));
    matrix.push_back(vector<int>(temp, temp+3));
    matrixCorrect.push_back(vector<int>(3, 0));
    matrixCorrect.push_back(vector<int>(3, 0));
    matrixCorrect.push_back(vector<int>(3, 0));
    chapter1.Problem_7(matrix);
    if(matrix!=matrixCorrect)
	return false;


    matrix.clear();
    matrixCorrect.clear();
    int size = 100;
    vector<int> temp1;
    for(unsigned i=0; i<size; ++i)
	temp1.push_back(i+1);
    for(unsigned i=0; i<size; ++i)
	matrix.push_back(temp1);
    matrix[0][0]=0;
    matrix[size-1][size-1]=0;
    matrixCorrect = matrix;
    for(unsigned i=0; i<size; ++i){
	matrixCorrect[0][i]=0;
	matrixCorrect[i][0]=0;
	matrixCorrect[size-1][i]=0;
	matrixCorrect[i][size-1]=0;
    }
    chapter1.Problem_7(matrix);
    if(matrix!=matrixCorrect)
	return false;
    return true;
}
