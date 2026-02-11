arch_prepare_kprobe(struct kprobe *p)
{
	if (alternatives_text_reserved(p->addr, p->addr))
		return -EINVAL;

	if (!can_probe((unsigned long)p->addr))
		return -EILSEQ;

	p->ainsn.insn = get_insn_slot();
	if (!p->ainsn.insn)
		return -ENOMEM;

	return arch_copy_kprobe(p);
}
