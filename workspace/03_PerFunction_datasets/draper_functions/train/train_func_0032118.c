Escapes1(const unsigned int anBoard[25], int n)
{

    int i, af = 0, m;

    m = (n < 12) ? n : 12;

    for (i = 0; i < m; i++)
        af |= (anPoint[anBoard[24 + i - n]] << i);

    return anEscapes1[af];
}
