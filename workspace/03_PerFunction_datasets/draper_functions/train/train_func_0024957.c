m1(F *r,F *x,F *y,I l,I n){F *q=y+1,a,b;a=b=0;
 DO(l,a+=*x**y;y+=n;b+=*x++**q;q+=n)*r=a,r[1]=b;}
