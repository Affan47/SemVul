out_rounddown(int width, unsigned long long n, unsigned long unit, int inc) {
    printf("%*llu", width, inc + n / unit);
    if (unit != 1)
	putchar((n % unit) ? '+' : ' ');
    putchar(' ');
}
