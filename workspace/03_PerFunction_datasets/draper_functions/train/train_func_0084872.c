GenPrime(BigInt& n, int digNum)
{
    int i = 0;
    BigInt divisor;
    const int length = sizeof(prime) / sizeof(int);
    while (i != length)
    {
        n.Random(digNum);
        while (!n.IsOdd())
            n.Random(digNum);
        i = 0;
        for ( ; i < length; i++)
        {
            divisor = prime[i];
            if ((n % divisor) == 0)
                break;
        }
    }
}
