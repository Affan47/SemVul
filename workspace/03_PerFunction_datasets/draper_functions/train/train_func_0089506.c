scadd(double *vec1, int beg, int end, double fac, double *vec2)
{
    int i;

    vec1 = vec1 + beg;
    vec2 = vec2 + beg;
    for (i = end - beg + 1; i; i--) {
	(*vec1++) += fac * (*vec2++);
    }
}
