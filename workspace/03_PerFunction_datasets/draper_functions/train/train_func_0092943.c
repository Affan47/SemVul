createQuickBWT(const std::string& str, BWT*& pBWT, SuffixArray*& pSA)
{
    ReadTable rt;
    SeqItem si = { "a", str };
    rt.addRead(si);

    pSA = new SuffixArray(&rt, 1, true);
    pBWT = new BWT(pSA, &rt);


}
