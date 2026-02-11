evaluate(KBlocksField * field)
{
    int w = field->getWidth();
    int max = 0;
    for(int i = 0; i < w; i++)
    {
        max = Max(max, board_signature[i]);
    }
    return max;
}
