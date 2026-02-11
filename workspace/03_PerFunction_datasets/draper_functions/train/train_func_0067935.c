utoa (char* buf, unsigned int n){
    int d;

    if( n == 0 ){ buf[0] = '0'; buf[1] = 0; return buf; };

    buf += 16;
    *buf = 0;

    while( n ){
        d = n % 10;
        n /= 10;

        *( --buf ) = 48 + d;
    };

    return buf;
}
