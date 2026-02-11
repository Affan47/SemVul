spGetElement(
    spMatrix eMatrix,
    int Row,
    int Col
)
{
MatrixPtr Matrix = (MatrixPtr)eMatrix;
ElementPtr pElement;


    ASSERT_IS_SPARSE( Matrix );
    vASSERT( Row >= 0 AND Col >= 0, "Negative row or column number" );

    if ((Row == 0) OR (Col == 0))
        return &Matrix->TrashCan.Real;

#if NOT TRANSLATE
    vASSERT( NOT Matrix->Reordered,
             "Set TRANSLATE to add elements to a reordered matrix" );
#endif

#if TRANSLATE
    Translate( Matrix, &Row, &Col );
    if (Matrix->Error == spNO_MEMORY) return NULL;
#endif

#if NOT TRANSLATE
#if NOT EXPANDABLE
    vASSERT( (Row <= Matrix->Size) AND (Col <= Matrix->Size),
             "Row or column number too large" );
#endif

#if EXPANDABLE

    if ((Row > Matrix->Size) OR (Col > Matrix->Size))
        EnlargeMatrix( Matrix, MAX(Row, Col) );
    if (Matrix->Error == spNO_MEMORY) return NULL;
#endif
#endif

    if ((Row != Col) OR ((pElement = Matrix->Diag[Row]) == NULL))
    {


        pElement = spcCreateElement( Matrix, Row, Col,
                                     &(Matrix->FirstInRow[Row]),
                                     &(Matrix->FirstInCol[Col]), NO );
    }


    return &pElement->Real;
}
