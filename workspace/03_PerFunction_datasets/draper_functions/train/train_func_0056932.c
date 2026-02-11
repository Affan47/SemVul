ajSortFloatDec(float *a, ajuint n)
{
    ajuint s;
    ajuint i;
    ajint j;
    float t;

    for(s=n/2; s>0; s /= 2)
	for(i=s; i<n; ++i)
	    for(j=i-s;j>=0 && a[j]<a[j+s]; j-=s)
	    {
		t = a[j];
		a[j] = a[j+s];
		a[j+s] = t;
	    }

    return;
}
