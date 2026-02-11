spcGetElement( MatrixPtr Matrix )
{
ElementPtr  pElement;


    if (Matrix->ElementsRemaining == 0)
    {   pElement = ALLOC(struct MatrixElement, ELEMENTS_PER_ALLOCATION);
        RecordAllocation( Matrix, (void *)pElement );
        if (Matrix->Error == spNO_MEMORY) return NULL;
        Matrix->ElementsRemaining = ELEMENTS_PER_ALLOCATION;
        Matrix->NextAvailElement = pElement;
    }


    Matrix->ElementsRemaining--;
    return Matrix->NextAvailElement++;
}
