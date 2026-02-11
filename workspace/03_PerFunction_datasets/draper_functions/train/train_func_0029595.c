free_flexsched_problem(flexsched_problem_t flex_prob) {
    int i;

    if (!flex_prob) return;

    for (i = 0; i < flex_prob->num_nodes; i++) {
        free_node(flex_prob->nodes[i]);
    }
    free(flex_prob->nodes);
    for (i = 0; i < flex_prob->num_jobs; i++) {
        free_job(flex_prob->jobs[i]);
    }
    free(flex_prob->jobs);
    free(flex_prob);
}
