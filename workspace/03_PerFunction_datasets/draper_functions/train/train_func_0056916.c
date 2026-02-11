column_max_height(int column, KBlocksField * field)
{
    int width = field->getWidth();
    int height = field->getHeight();

    if ((column < 0) || (column >= width))
    {

    }

    for(int j = 0; j < height; j++)
    {
        if(field->getCell(column,j))
        {
            return j;
        }
    }
    return height;
}
