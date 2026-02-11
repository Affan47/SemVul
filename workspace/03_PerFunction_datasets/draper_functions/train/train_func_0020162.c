sort_ranks (aalist)
struct rank_cell aalist[AAS];
{
        int i, j;
        struct rank_cell tmp;


        for (i = 2; i < AAS; i++) {
                tmp.aa = aalist[i].aa;
                tmp.value = aalist[i].value;
                for (j = i; j > 1 && aalist[j-1].value < tmp.value; j--) {
                        aalist[j].value = aalist[j-1].value;
                        aalist[j].aa = aalist[j-1].aa;
                }
                aalist[j].value = tmp.value;
                aalist[j].aa = tmp.aa;
        }
}
