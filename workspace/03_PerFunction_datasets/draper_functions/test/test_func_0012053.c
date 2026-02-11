lightt( elemnt, q, e )
double e[], q[];
struct orbit *elemnt;
{
double p[3], p0[3], ptemp[3];
double P, Q, E, t, x, y;
int i, k;


for( i=0; i<3; i++ )
	{
	p0[i] = q[i] - e[i];
	}

E = 0.0;
for( i=0; i<3; i++ )
	E += e[i]*e[i];
E = sqrt(E);

for( k=0; k<2; k++ )
	{
	P = 0.0;
	Q = 0.0;
	for( i=0; i<3; i++ )
		{
		y = q[i];
		x = y - e[i];
		p[i] = x;
		Q += y * y;
		P += x * x;
		}
	P = sqrt(P);
	Q = sqrt(Q);

	t = (P + 1.97e-8 * log( (E+P+Q)/(E-P+Q) ) )/173.1446327;
	kepler( TDT-t, elemnt, q, ptemp );
	}

if( prtflg )
	printf( "light time %.4fm,  ", 1440.0*t );


for( i=0; i<3; i++ )
	{
	x = q[i] - e[i];
	p[i] = x;
	dp[i] = x - p0[i];
	}
showcor( "aberration", p0, dp );


velearth(TDT);
for( i=0; i<3; i++ )
	p[i] += vearth[i]*t;

deltap( p, p0, &dradt, &ddecdt );
dradt /= t;
ddecdt /= t;
return(0);
}
