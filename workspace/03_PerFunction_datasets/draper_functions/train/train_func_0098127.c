fp2pow(p,D,uu,n)
unsigned p,D;
unsigned *uu;
unsigned n;
{
    word4 x,x0,y,y0,X,Y;

    if(n == 0) {
        uu[0] = 1;
        uu[1] = 0;
        return;
    }
    x = uu[0]; y = uu[1];
    X = 1; Y = 0;
    while(n > 1) {
        if(n & 1) {
            x0 = X;
            y0 = (Y*y) % p;


            X *= x;    X %= p;
            X += D*y0; X %= p;
            Y *= x;    X %= p;
            Y += x0*y; Y %= p;
        }
        x0 = x;
        y0 = (y*y) % p;


        x *= x;    x %= p;
        x += D*y0; x %= p;
        y *= x0;   y %= p;
        y += y;    y %= p;
        n >>= 1;
    }
    x0 = X;
    y0 = (Y*y) % p;


    X *= x; X %= p;
    X += D*y0;
    uu[0] = X % p;
    Y *= x;
    Y += x0*y;
    uu[1] = Y % p;
}
