search(AWT_species_set *set,long *best_co){
    AWT_species_set *result = 0;
    long i;
    long best_cost = 0x7fffffff;
    unsigned char *sbs = set->bitstring;
    for (i=nsets-1;i>=0;i--){
        long j;
        long sum = 0;
        unsigned char *rsb = sets[i]->bitstring;
        for (j=nspecies/8 -1 + 1; j>=0;j--){
            sum += diff_bits[ (sbs[j]) ^ (rsb[j]) ];
        }
        if (sum > nspecies/2) sum = nspecies - sum;
        if (sum < best_cost){
            best_cost = sum;
            result = sets[i];
        }
    }
    *best_co = best_cost;
    return result;
}
