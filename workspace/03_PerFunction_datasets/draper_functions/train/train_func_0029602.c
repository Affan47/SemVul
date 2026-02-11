VHiSax_putstatus(struct IsdnCardState *cs, char *head, char *fmt,
		      va_list args)
{


	u_long		flags;
	int		count, i;
	u_char		*p;
	isdn_ctrl	ic;
	int		len;

	if (!cs) {
		printk(KERN_WARNING "HiSax: No CardStatus for message");
		return;
	}
	spin_lock_irqsave(&cs->statlock, flags);
	p = tmpbuf;
	if (head) {
		p += jiftime(p, jiffies);
		p += sprintf(p, " %s", head);
		p += vsprintf(p, fmt, args);
		*p++ = '\n';
		*p = 0;
		len = p - tmpbuf;
		p = tmpbuf;
	} else {
		p = fmt;
		len = strlen(fmt);
	}
	if (len > HISAX_STATUS_BUFSIZE) {
		spin_unlock_irqrestore(&cs->statlock, flags);
		printk(KERN_WARNING "HiSax: status overflow %d/%d\n",
		       len, HISAX_STATUS_BUFSIZE);
		return;
	}
	count = len;
	i = cs->status_end - cs->status_write + 1;
	if (i >= len)
		i = len;
	len -= i;
	memcpy(cs->status_write, p, i);
	cs->status_write += i;
	if (cs->status_write > cs->status_end)
		cs->status_write = cs->status_buf;
	p += i;
	if (len) {
		memcpy(cs->status_write, p, len);
		cs->status_write += len;
	}
#ifdef KERNELSTACK_DEBUG
	i = (ulong) & len - current->kernel_stack_page;
	sprintf(tmpbuf, "kstack %s %lx use %ld\n", current->comm,
		current->kernel_stack_page, i);
	len = strlen(tmpbuf);
	for (p = tmpbuf, i = len; i > 0; i--, p++) {
		*cs->status_write++ = *p;
		if (cs->status_write > cs->status_end)
			cs->status_write = cs->status_buf;
		count++;
	}
#endif
	spin_unlock_irqrestore(&cs->statlock, flags);
	if (count) {
		ic.command = ISDN_STAT_STAVAIL;
		ic.driver = cs->myid;
		ic.arg = count;
		cs->iif.statcallb(&ic);
	}
}
