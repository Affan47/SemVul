fibBottomUp(const int &n) {

    if (n == 1 || n == 2)
        return 1;

    ull first = 1;
    ull second = 1;
    ull fib;


    for (int i = 3; i <= n; ++i) {
        fib = first + second;
        first = second;
        second = fib;
    }

    return fib;
}
