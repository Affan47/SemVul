vm_events_fold_cpu(int cpu)
{
	struct vm_event_state *fold_state = &per_cpu(vm_event_states, cpu);
	int i;

	for (i = 0; i < NR_VM_EVENT_ITEMS; i++) {
		count_vm_events(i, fold_state->event[i]);
		fold_state->event[i] = 0;
	}
}
