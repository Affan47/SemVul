compute_utilization(flexsched_solution_t flex_soln)
{
    int i;
    double total_capacity = 0.0;
    double total_alloc = 0.0;

    for (i = 0; i < flex_soln->prob->num_nodes; i++) {
        total_capacity +=
            double_array_sum(flex_soln->prob->nodes[i]->total_capacities,
                flex_soln->prob->num_resources);
    }

    if (total_capacity <= 0.0) return 1.0;

    for (i = 0; i < flex_soln->prob->num_jobs; i++) {
        total_alloc +=
            double_array_sum(
                flex_soln->prob->jobs[i]->total_rigid_requirements,
                flex_soln->prob->num_resources) +
            flex_soln->yields[i] *
              double_array_sum(flex_soln->prob->jobs[i]->total_fluid_needs,
                    flex_soln->prob->num_resources);
    }

    return (total_alloc / total_capacity);
}
