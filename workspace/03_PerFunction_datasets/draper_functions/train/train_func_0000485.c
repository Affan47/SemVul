distribute_remainder(sLad *lad, SymRegion *lr_region_head)
{
    int order;
    SemTree *div_order;
    SemTree *tmp;

    SymRegion *region;

    SemTree *rem;
    SemTree *n1;
    SemTree *alpha;
    SemTree *beta;
    SemTree *db;
    SemTree *de;

    const SemTree *const_one = lad->sym_const_one;
    SemTree *new_begin;
    SemTree *new_end;


    tmp = make_semtree(OPE_MUL, lad->sym_gsrngd, lad->sym_div_num);
    rem = make_semtree(OPE_SUB, lad->sym_gsrng, tmp);

    n1 = make_semtree(OPE_SUB, lad->sym_div_num, rem);

#ifdef DEBUG_SYM_LAD
    fprintf(stderr, "rem = ");
    fput_semtree(stderr, semtree_process_divide(semtree_dup(rem)));
    fprintf(stderr, "\n");

    fprintf(stderr, "n1  = ");
    fput_semtree(stderr, semtree_process_divide(semtree_dup(rem)));
    fprintf(stderr, "\n");
#endif

    region = lr_region_head;
    for(order = 0; order < lad->div_num; order++) {
        if (region == NULL) {
            continue;
        }

        div_order = make_semtree_const_int(order);


        tmp = make_semtree(OPE_ADD, div_order, rem);
        alpha = make_semtree(OPE_DIV, tmp, lad->sym_div_num);


        beta = make_semtree(OPE_SUB, div_order, n1);

        db = make_semtree(OPE_MUL, alpha, beta);
        tmp = make_semtree(OPE_ADD, beta, const_one);
        de = make_semtree(OPE_MUL, alpha, tmp);

#ifdef DEBUG_SYM_LAD
        fprintf(stderr, "[order=%d] ", order);

        semtree_process_divide(alpha);
        fprintf(stderr, "alpha = ");
        fput_semtree(stderr, alpha);
        fprintf(stderr, ", ");

        semtree_process_divide(beta);
        fprintf(stderr, "beta = ");
        fput_semtree(stderr, beta);
        fprintf(stderr, ", ");

        semtree_process_divide(db);
        fprintf(stderr, "db = ");
        fput_semtree(stderr, db);
        fprintf(stderr, ", ");

        semtree_process_divide(de);
        fprintf(stderr, "de = ");
        fput_semtree(stderr, de);
        fprintf(stderr, "\n");
#endif

        new_begin = make_semtree(OPE_ADD, region->begin, db);
        semtree_process_divide(new_begin);
        region->begin = new_begin;

        if (order != lad->div_num - 1) {
            new_end = make_semtree(OPE_ADD, region->end, de);
            semtree_process_divide(new_end);
            region->end = new_end;
        }

        region = region->next;
    }
}
