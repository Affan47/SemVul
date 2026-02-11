line_get(const struct lineop *op)
{
	u8 oldval = port_read(op->port);

	return ((op->inverted && (oldval & op->val) != op->val)
	    || (!op->inverted && (oldval & op->val) == op->val));
}
