x86_64_get_xendump_regs(struct xendump_data *xd, struct bt_info *bt, ulong *rip, ulong *rsp)
{
	ulong task, xrip, xrsp;
	off_t offset;
	struct syment *sp;
	char *rip_symbol;
	int cpu;

        if (INVALID_MEMBER(vcpu_guest_context_user_regs) ||
            INVALID_MEMBER(cpu_user_regs_rip) ||
            INVALID_MEMBER(cpu_user_regs_rsp))
                goto generic;

        offset = (off_t)xd->xc_core.header.xch_ctxt_offset +
                (off_t)OFFSET(vcpu_guest_context_user_regs) +
                (off_t)OFFSET(cpu_user_regs_rsp);
        if (lseek(xd->xfd, offset, SEEK_SET) == -1)
                goto generic;
        if (read(xd->xfd, &xrsp, sizeof(ulong)) != sizeof(ulong))
                goto generic;

        offset = (off_t)xd->xc_core.header.xch_ctxt_offset +
                (off_t)OFFSET(vcpu_guest_context_user_regs) +
                (off_t)OFFSET(cpu_user_regs_rip);
        if (lseek(xd->xfd, offset, SEEK_SET) == -1)
                goto generic;
        if (read(xd->xfd, &xrip, sizeof(ulong)) != sizeof(ulong))
                goto generic;


        if (IS_KVADDR(xrsp) && (task = stkptr_to_task(xrsp)) &&
	    (task == bt->task)) {
		if (CRASHDEBUG(1))
			fprintf(xd->ofp,
		"hooks from vcpu_guest_context: rip: %lx rsp: %lx\n", xrip, xrsp);
		*rip = xrip;
		*rsp = xrsp;
		return;
	}

generic:

	machdep->get_stack_frame(bt, rip, rsp);


	if (is_task_active(bt->task) && (rip_symbol = closest_symbol(*rip)) &&
	    (STREQ(rip_symbol, "thread_return") || STREQ(rip_symbol, "schedule"))) {
		cpu = bt->tc->processor;
		xrsp = machdep->machspec->stkinfo.ibase[cpu] +
			machdep->machspec->stkinfo.isize - sizeof(ulong);

                while (readmem(xrsp, KVADDR, &xrip,
                    sizeof(ulong), "xendump rsp", RETURN_ON_ERROR)) {
        		if ((sp = value_search(xrip, (ulong *)&offset)) &&
			    STREQ(sp->name, "smp_really_stop_cpu") && offset) {
                                *rip = xrip;
                                *rsp = xrsp;
                                if (CRASHDEBUG(1))
                                        error(INFO,
                                            "switch thread_return to smp_call_function_interrupt\n");
                                break;
                        }
                        xrsp -= sizeof(ulong);
                        if (xrsp <= machdep->machspec->stkinfo.ibase[cpu])
                                break;
                }
	}
}
