define_label(int label, State * state)
{
    unsigned value = state->num_bytes;

    while (label != -1) {
	Fixup *fixup = &(state->fixups[label]);

	fixup->value = value;
	fixup->prev_literals = state->num_literals;
	fixup->prev_forks = state->num_forks;
	fixup->prev_var_refs = state->num_var_refs;
	fixup->prev_labels = state->num_labels;
	fixup->prev_stacks = state->num_stacks;
	label = fixup->next;
    }
}
