getOuts()
{
    int ret = Wlen[aces];
    for ( int i = 0; i < 8 * 3; i++ )
        ret += Wlen[i];
    return ret;
}
