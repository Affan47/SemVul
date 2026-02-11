CORD_add_forest(ForestElement * forest, CORD x, size_t len)
{
    register int i = 0;
    register CORD sum = CORD_EMPTY;
    register size_t sum_len = 0;

    while (len > min_len[i + 1]) {
        if (forest[i].c != 0) {
            sum = CORD_cat(forest[i].c, sum);
            sum_len += forest[i].len;
            forest[i].c = 0;
        }
        i++;
    }


    sum = CORD_cat(sum, x);
    sum_len += len;


    while (sum_len >= min_len[i]) {
        if (forest[i].c != 0) {
            sum = CORD_cat(forest[i].c, sum);
            sum_len += forest[i].len;


            forest[i].c = 0;
        }
        i++;
    }
    i--;
    forest[i].c = sum;
    forest[i].len = sum_len;
}
