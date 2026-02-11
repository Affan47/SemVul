checkParameterDim(vector<vector<unsigned int> > const &dims) const
{
    return isScalar(dims[0]) && isScalar(dims[1]) && isSquareMatrix(dims[2]);
}
