convert_matrix_ff(std::vector<std::vector<double> > &src, double **dst)
{
    unsigned int i, j;

    for ( i = 0 ; i < src.size() ; i++ )
        for ( j = 0 ; j < src[i].size() ; j++ )
            dst[i][j] = src[i][j];

    return true;
}
