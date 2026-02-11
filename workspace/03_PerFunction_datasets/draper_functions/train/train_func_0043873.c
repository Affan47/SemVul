set_block_cost_for_hetero(char *cost_file)
{
    FILE *fp;
    char file[256];
    char buf[256];
    int hmt_num;
    int mtno;
    int mtcost;
    int line = 0;
    real *cost = NULL;

    if (cost_file == NULL) {
        return NULL;
    }

    strcpy(file, cost_file);
    fprintf(stderr, "Opening Cost File %s...\n", file);
    if ((fp = fopen(file, "r")) == NULL) {
        fprintf(stderr, "Cannot Open Cost File for HETERO Static Scheduling");
        return NULL;
    }

    if (fgets(buf, sizeof(buf), fp) == NULL) {
        fprintf(stderr, "Unexpected Format!!\n");
        fclose(fp);
        return NULL;
    }
    sscanf(buf, "%d", &hmt_num);
    if (hmt_num != get_max_hmt_no() || hmt_num <= 0) {
        fprintf(stderr,
                "Invalid Number of MTs(%d) !! (Max hmt_no = %d)\n",
                hmt_num, get_max_hmt_no());
        fclose(fp);
        return NULL;
    }

    cost = zcalloc(hmt_num + 1, sizeof(real));
    do {
        if (fgets(buf, sizeof(buf), fp) == NULL) {
            break;
        }
        sscanf(buf, "%d%d", &mtno, &mtcost);
        if (mtcost > 0) {
            cost[mtno] = (real)mtcost;
        } else {
            cost[mtno] = -1.0;
        }
        line++;
    } while (fp != NULL);
    if (line != hmt_num) {
        fprintf(stderr, "Invalid Number of Lines!!\n");
        fclose(fp);
        free(cost);
        return NULL;
    }
    fclose(fp);
    return cost;
}
