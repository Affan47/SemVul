SetDimensionCount(unsigned char nDim)
{
    if(nDim < 1 || nDim > 8)
    {
        throw PCIDSKException("An array cannot have a "
            "dimension bigger than 8 or smaller than 1.");
    }
    mnDimension = nDim;
    mbModified = true;
}
