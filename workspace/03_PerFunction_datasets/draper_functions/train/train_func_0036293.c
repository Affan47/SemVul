evaluate(KBlocksField * field)
{
    int w = field->getWidth();
    int lh = 0;
    int ch = board_signature[0];
    int rh = board_signature[1];
    int max = 0;
    if(ch < rh)
    {
        max = Max(max, rh - ch);
    }
    for(int i = 2; i < w; i++)
    {
        lh = ch;
        ch = rh;
        rh = column_max_height(i, field);
        if ((lh > ch) && (rh > ch))
        {
            max= Max(max, Min(lh - ch, rh - ch));
        }
    }
    if(ch > rh)
    {
        max = Max(max, ch - rh);
    }
    return max;
}
