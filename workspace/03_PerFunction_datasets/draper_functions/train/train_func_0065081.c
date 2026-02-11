countDifferences(const std::string& s1, const std::string& s2, size_t n)
{
    int numDiff = 0;
    for(size_t i = 0; i < n; ++i)
    {
        if(s1[i] != s2[i])
            numDiff++;
    }
    return numDiff;
}
