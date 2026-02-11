arch_optimize_kprobes(struct list_head *oplist)
{
	struct optimized_kprobe *op, *tmp;
	u8 insn_buf[RELATIVEJUMP_SIZE];

	list_for_each_entry_safe(op, tmp, oplist, list) {
		s32 rel = (s32)((long)op->optinsn.insn -
			((long)op->kp.addr + RELATIVEJUMP_SIZE));

		WARN_ON(kprobe_disabled(&op->kp));


		memcpy(op->optinsn.copied_insn, op->kp.addr + INT3_SIZE,
		       RELATIVE_ADDR_SIZE);

		insn_buf[0] = RELATIVEJUMP_OPCODE;
		*(s32 *)(&insn_buf[1]) = rel;

		text_poke_bp(op->kp.addr, insn_buf, RELATIVEJUMP_SIZE,
			     op->optinsn.insn);

		list_del_init(&op->list);
	}
}
