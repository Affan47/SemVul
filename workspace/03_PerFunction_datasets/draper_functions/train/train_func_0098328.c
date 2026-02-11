FBPolygon(Pixel,Type,StyleId,xy,n)

int Pixel,Type,StyleId,n;
int *xy;
{


    int j,n2,X,Y,Z,T,Xo,Yo;
    Poly poly;
    FBForeground(DISPLAY,Pixel);
    (*GR[FB.fInterface].gSetFp)(StyleId);

    poly.xy = xy;

    while (NewPolygon(&poly)) {
        n = poly.nvertices;

        if (Type == OUTLINE) {
            n2 = n + n;
            j = 2;
            Xo = X = xy[0];
            Yo = Y = xy[1];
            while (j < n2) {
                Z = xy[j++];
                T = xy[j++];
                (*GR[FB.fInterface].gLine)(X,Y,Z,T);
                X = Z;
                Y = T;
            }
            (*GR[FB.fInterface].gLine)(X,Y,Xo,Yo);
        }
        else {
            if (n < 2) return;
            (*GR[FB.fInterface].gPolygon)(&poly);
        }
    }
}
