copy(FieldInterface * p)
{
    for(int i = 0; i < mHeight; i++)
    {
        for(int j = 0; j < mWidth; j++)
        {
            maBoard[i][j] = p->getCell(j, i);
        }
    }
}
