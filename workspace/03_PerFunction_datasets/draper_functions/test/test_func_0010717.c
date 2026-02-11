realabs_comp(a,b)
REAL *a,*b;
{if(fabs(*a)<fabs(*b))return-1;else if (fabs(*a)>fabs(*b))return 1;return 0;}
