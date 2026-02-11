extended( int a, int b, int* s, int* t ) {
    lli x = 0, y = 1, lastx = 1, lasty = 0, q, temp;

    while ( b != 0 ) {
        q = a / b;
        temp = b;
        b = a % b;
        a = temp;
        temp = x;
        x = lastx - q * x;
        lastx = temp;
        temp = y;
        y = lasty - q * y;
        lasty = temp;
    }
    *s = lastx;
    *t = lasty;
}
