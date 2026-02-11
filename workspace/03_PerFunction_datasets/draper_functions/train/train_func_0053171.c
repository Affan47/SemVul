Range(REAL NormSquared){
    if (A==NULL)
        Create();


    while (NormSquared * 4 > maxNormSquared && maxNormSquared < se_maxGridSize )
        Grow();
}
