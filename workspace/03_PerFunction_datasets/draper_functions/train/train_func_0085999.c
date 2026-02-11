fcmpf (int* ip1, int* ip2)
{
    float d1 = fvals[*ip1];
    float d2 = fvals[*ip2];
    if (d1 < d2) return -1;
    else if (d1 > d2) return 1;
    else return 0;
}
