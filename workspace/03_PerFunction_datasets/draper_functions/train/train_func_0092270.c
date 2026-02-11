reversePoints()

{
    int i;

    for( i = 0; i < nPointCount/2; i++ )
    {
        OGRRawPoint sPointTemp = paoPoints[i];

        paoPoints[i] = paoPoints[nPointCount-i-1];
        paoPoints[nPointCount-i-1] = sPointTemp;

        if( padfZ )
        {
            double dfZTemp = padfZ[i];

            padfZ[i] = padfZ[nPointCount-i-1];
            padfZ[nPointCount-i-1] = dfZTemp;
        }
    }
}
