unit_requirements_within_capacity(
    flexsched_problem_t flex_prob, int job, int node)
{
    int i;
    for (i = 0; i < flex_prob->num_resources; i++) {
        if (!unit_requirements_within_capacity_in_dim(flex_prob, job,
            node, i)) return 0;
    }
    return 1;
}
