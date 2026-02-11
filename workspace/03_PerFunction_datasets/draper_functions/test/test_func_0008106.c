calc_perm_exp(object *op) {
    sint64 p_exp_min;


    p_exp_min = settings.permanent_exp_ratio*op->stats.exp/100;

    if (op->perm_exp < p_exp_min)
        op->perm_exp = p_exp_min;


    if (op->perm_exp < 0)
        op->perm_exp = 0;
    else if (op->perm_exp > MAX_EXPERIENCE)
        op->perm_exp = MAX_EXPERIENCE;
}
