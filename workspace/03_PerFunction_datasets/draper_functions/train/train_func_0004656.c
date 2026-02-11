call_vp_algo(vp_algo_t algo,
    vp_problem_t vp_prob)
{
    vp_solution_t vp_soln = algo->solver(vp_prob, algo->args,
        algo->cmp_item_idxs, algo->cmp_bin_idxs);

    if (vp_soln) strcpy(vp_soln->misc_output, algo->name);

    return vp_soln;
}
