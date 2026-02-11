power(int a, unsigned int n) {

    if (n == 1)
        return a;
    return a*power(a, n-1);
}
