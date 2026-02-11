statHistCount(StatHist * H, double val)
{
    const int bin = statHistBin(H, val);
    assert(H->bins);
    assert(0 <= bin && bin < H->capacity);
    H->bins[bin]++;
}
