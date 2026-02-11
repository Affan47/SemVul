Compare(Position * p)
{
    int i = 32;
    unsigned char *p1, *p2;
    p1 = Board;
    p2 = p->Board;
    while(i   &&  *p1 == *p2)
    {
        i--;
        p1++;
        p2++;
    }
    if(p1 < p2)
    {
        return -1;
    }
    if(p1 > p2)
    {
        return 1;
    }
    return (ToMove - p->GetToMove());
}
