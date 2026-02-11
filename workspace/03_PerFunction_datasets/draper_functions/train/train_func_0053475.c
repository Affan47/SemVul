set_mask(uint32_t full_mask, int shift, uint32_t provided_mask, ErrorHandler *errh)
{
    uint32_t data = _u.u;
    uint32_t this_mask = (provided_mask ? provided_mask : full_mask);
    if ((this_mask & full_mask) != this_mask)
	return errh->error("mask 0x%X out of range (0-0x%X)", provided_mask, full_mask);

    if (_op == OP_GT || _op == OP_LT) {

	if ((_op == OP_LT && (data == 0 || data > this_mask))
	    || (_op == OP_GT && data >= this_mask)) {
	    bool will_be = (_op == OP_LT && data > this_mask ? !_op_negated : _op_negated);
	    errh->warning("relation '%s %u' is always %s (range 0-%u)", unparse_op().c_str(), data, (will_be ? "true" : "false"), this_mask);
	    _u.u = _mask.u = 0;
	    _op_negated = !will_be;
	    _op = OP_EQ;
	    return 0;
	}


	if (_op == OP_LT) {
	    _u.u--;
	    _op_negated = !_op_negated;
	    _op = OP_GT;
	}

	_u.u = (_u.u << shift) | ((1 << shift) - 1);
	_mask.u = (this_mask << shift) | ((1 << shift) - 1);


	if ((_u.u & _mask.u) != _u.u) {
	    uint32_t full_mask_u = (full_mask << shift) | ((1 << shift) - 1);
	    uint32_t missing_bits = (_u.u & _mask.u) ^ (_u.u & full_mask_u);
	    uint32_t add_mask = 0xFFFFFFFFU >> ffs_msb(missing_bits);
	    _u.u = (_u.u | add_mask) & _mask.u;
	}
	return 0;
    }

    if (data > full_mask)
	return errh->error("value %u out of range (0-%u)", data, full_mask);

    _u.u = data << shift;
    _mask.u = this_mask << shift;
    return 0;
}
