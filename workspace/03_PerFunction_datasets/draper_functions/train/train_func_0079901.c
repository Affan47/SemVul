control_reg_set_pid(struct m66592 *m66592, u16 pipenum,
		u16 pid)
{
	unsigned long offset;

	if (pipenum == 0)
		m66592_mdfy(m66592, pid, M66592_PID, M66592_DCPCTR);
	else if (pipenum < M66592_MAX_NUM_PIPE) {
		offset = get_pipectr_addr(pipenum);
		m66592_mdfy(m66592, pid, M66592_PID, offset);
	} else
		pr_err("unexpect pipe num (%d)\n", pipenum);
}
