get_kvmdump_regs(struct bt_info *bt, ulong *ipp, ulong *spp)
{
	ulong ip, sp;
	struct register_set *rp;

	ip = sp = 0;

	if (!is_task_active(bt->task)) {
		machdep->get_stack_frame(bt, ipp, spp);
		return;
	}

	bt->flags |= BT_DUMPFILE_SEARCH;
	if (machine_type("X86_64"))
		machdep->get_stack_frame(bt, ipp, spp);
	else if (machine_type("X86"))
		get_netdump_regs_x86(bt, ipp, spp);
	if (bt->flags & BT_DUMPFILE_SEARCH)
		return;

	if ((kvm->registers == NULL) ||
	    (bt->tc->processor >= kvm->cpu_devices))
		return;

	rp = &kvm->registers[bt->tc->processor];
	ip = (ulong)rp->ip;
	sp = (ulong)rp->regs[R_ESP];
	if (is_kernel_text(ip) &&
	    (((sp >= GET_STACKBASE(bt->task)) &&
	      (sp < GET_STACKTOP(bt->task))) ||
	    in_alternate_stack(bt->tc->processor, sp))) {
		*ipp = ip;
		*spp = sp;
		bt->flags |= BT_KERNEL_SPACE;
		return;
	}

	if (!is_kernel_text(ip) &&
	    in_user_stack(bt->tc->task, sp))
		bt->flags |= BT_USER_SPACE;
}
