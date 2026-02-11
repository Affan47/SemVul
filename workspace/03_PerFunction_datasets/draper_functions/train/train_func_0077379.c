ompi_group_calc_sporadic ( int n , const int *ranks)
{
    int i,l=0;
    for (i=0 ; i<n ; i++) {
        if(ranks[i] == ranks[i-1]+1) {
            if(l==0) {
                l++;
            }
        }
        else {
            l++;
        }
    }
    return sizeof(struct ompi_group_sporadic_list_t ) * l;
}
