parse_exec_spec_get_cpu(int logical_cpu, struct argp_state *state)
{
    if (!num_mappings)
	return logical_cpu;

    if (logical_cpu >= num_mappings)
	argp_error(state, "Error: No mapping for logical CPU '%i'.\n",
                   logical_cpu);

    return cpu_map[logical_cpu];
}
