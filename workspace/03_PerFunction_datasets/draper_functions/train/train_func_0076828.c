_depth(struct rx_node *r, unsigned leftmost)
{
	int count = 1;

	while (r->type != CHARSET && LEFT(r) && (leftmost || r->type != OR)) {
		count++;
		r = LEFT(r);
	}

	return count;
}
