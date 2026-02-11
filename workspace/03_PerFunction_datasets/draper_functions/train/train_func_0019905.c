__do_cpuid_ent_emulated(struct kvm_cpuid_entry2 *entry,
				   u32 func, u32 index, int *nent, int maxnent)
{
	switch (func) {
	case 0:
		entry->eax = 1;
		++*nent;
		break;
	case 1:
		entry->ecx = F(MOVBE);
		++*nent;
		break;
	default:
		break;
	}

	entry->function = func;
	entry->index = index;

	return 0;
}
