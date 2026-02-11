spMNA_Preorder( spMatrix eMatrix )
{
MatrixPtr  Matrix = (MatrixPtr)eMatrix;
register  int  J, Size;
ElementPtr  pTwin1=0, pTwin2=0;
int  Twins, StartAt = 1;
BOOLEAN  Swapped, AnotherPassNeeded;


    ASSERT_IS_SPARSE( Matrix );
    ASSERT_NO_ERRORS( Matrix );
    ASSERT_IS_NOT_FACTORED( Matrix );

    if (Matrix->RowsLinked) return;
    Size = Matrix->Size;
    Matrix->Reordered = YES;

    do
    {   AnotherPassNeeded = Swapped = NO;


        for (J = StartAt; J <= Size; J++)
        {   if (Matrix->Diag[J] == NULL)
            {   Twins = CountTwins( Matrix, J, &pTwin1, &pTwin2 );
                if (Twins == 1)
                {
                    SwapCols( Matrix, pTwin1, pTwin2 );
                    Swapped = YES;
                }
                else if ((Twins > 1) AND NOT AnotherPassNeeded)
                {   AnotherPassNeeded = YES;
                    StartAt = J;
                }
            }
        }


        if (AnotherPassNeeded)
        {   for (J = StartAt; NOT Swapped AND (J <= Size); J++)
            {   if (Matrix->Diag[J] == NULL)
                {   Twins = CountTwins( Matrix, J, &pTwin1, &pTwin2 );
                    SwapCols( Matrix, pTwin1, pTwin2 );
                    Swapped = YES;
                }
            }
        }
    } while (AnotherPassNeeded);
    return;
}
