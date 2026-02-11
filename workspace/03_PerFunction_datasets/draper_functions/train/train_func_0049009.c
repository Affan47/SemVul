cmdbuf_add(struct pt3_i2cbuf *cbuf, enum ctl_cmd cmd)
{
	int buf_idx;

	if ((cbuf->num_cmds % 2) == 0)
		cbuf->tmp = cmd;
	else {
		cbuf->tmp |= cmd << 4;
		buf_idx = cbuf->num_cmds / 2;
		if (buf_idx < ARRAY_SIZE(cbuf->data))
			cbuf->data[buf_idx] = cbuf->tmp;
	}
	cbuf->num_cmds++;
}
