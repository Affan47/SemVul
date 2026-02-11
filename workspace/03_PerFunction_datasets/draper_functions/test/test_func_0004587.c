ExchangeRowElements(
    MatrixPtr Matrix,
    int  Col1,
    register ElementPtr Element1,
    int  Col2,
    register ElementPtr Element2,
    int  Row
)
{
ElementPtr  *ElementLeftOfCol1, *ElementLeftOfCol2;
ElementPtr  ElementRightOfCol1, ElementRightOfCol2;
register   ElementPtr  pElement;


    ElementLeftOfCol1 = &(Matrix->FirstInRow[Row]);
    pElement = *ElementLeftOfCol1;
    while (pElement->Col < Col1)
    {   ElementLeftOfCol1 = &(pElement->NextInRow);
        pElement = *ElementLeftOfCol1;
    }
    if (Element1 != NULL)
    {   ElementRightOfCol1 = Element1->NextInRow;
        if (Element2 == NULL)
        {

            if ( ElementRightOfCol1 != NULL AND ElementRightOfCol1->Col < Col2 )
            {

                *ElementLeftOfCol1 = ElementRightOfCol1;


                pElement = ElementRightOfCol1;
                do
                {   ElementLeftOfCol2 = &(pElement->NextInRow);
                    pElement = *ElementLeftOfCol2;
                }   while (pElement != NULL AND pElement->Col < Col2);


                *ElementLeftOfCol2 = Element1;
                Element1->NextInRow = pElement;
                *ElementLeftOfCol1 =ElementRightOfCol1;
            }
            Element1->Col = Col2;
        }
        else
        {

            if ( ElementRightOfCol1->Col == Col2)
            {

                Element1->NextInRow = Element2->NextInRow;
                Element2->NextInRow = Element1;
                *ElementLeftOfCol1 = Element2;
            }
            else
            {

                pElement = ElementRightOfCol1;
                do
                {   ElementLeftOfCol2 = &(pElement->NextInRow);
                    pElement = *ElementLeftOfCol2;
                }   while (pElement->Col < Col2);

                ElementRightOfCol2 = Element2->NextInRow;


                *ElementLeftOfCol1 = Element2;
                Element2->NextInRow = ElementRightOfCol1;
                *ElementLeftOfCol2 = Element1;
                Element1->NextInRow = ElementRightOfCol2;
            }
            Element1->Col = Col2;
            Element2->Col = Col1;
        }
    }
    else
    {

        ElementRightOfCol1 = pElement;


        if (ElementRightOfCol1->Col != Col2)
        {   do
            {   ElementLeftOfCol2 = &(pElement->NextInRow);
                pElement = *ElementLeftOfCol2;
            }   while (pElement->Col < Col2);


            *ElementLeftOfCol2 = Element2->NextInRow;
            *ElementLeftOfCol1 = Element2;
            Element2->NextInRow = ElementRightOfCol1;
        }
        Element2->Col = Col1;
    }
    return;
}
