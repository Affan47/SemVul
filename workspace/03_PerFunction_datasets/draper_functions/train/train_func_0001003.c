sorb_decimal_print (char buf[], int n)
{
    int i;
    for (i = 0; i < n; ++i) {
	fprintf(stderr,"%4d ",buf[i]);
    }
    fprintf(stderr,"\n");
}
