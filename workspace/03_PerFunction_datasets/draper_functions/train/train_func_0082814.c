evaluate(KBlocksField * field)
{
    int w = field->getWidth();
    double average = 0;
    int h0 = board_signature[0];
    for(int i = 1; i < w; i++)
    {
        int h1 = board_signature[i];
        int dh = Abs(h1 - h0);
        h0 = h1;
        average += dh;
    }
    return average / (w-1);
}
