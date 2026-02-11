Initialize(const double **padfImg, int nHeight, int nWidth)
{

    pMatrix = new double*[nHeight];
    for (int i = 0; i < nHeight; i++)
        pMatrix[i] = new double[nWidth];

    this->nHeight = nHeight;
    this->nWidth = nWidth;


    for (int i = 0; i < nHeight; i++)
        for (int j = 0; j < nWidth; j++)
        {
            double val = padfImg[i][j];
            double a = 0, b = 0, c = 0;

            if (i - 1 >= 0 && j - 1 >= 0)
                a = pMatrix[i - 1][j - 1];
            if (j - 1 >= 0)
                b = pMatrix[i][j - 1];
            if (i - 1 >= 0)
                c = pMatrix[i - 1][j];


            pMatrix[i][j] = val - a + b + c;
        }
}
