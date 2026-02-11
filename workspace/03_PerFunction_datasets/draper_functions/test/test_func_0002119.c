configure(Vector<String> &conf, ErrorHandler *errh)
{
    if (Args(conf, this, errh).read("ACTIVE", _active).complete() < 0)
	return -1;
    if (!_active && input_is_push(0))
	return errh->error("ACTIVE is meaningless in push context");
    return 0;
}
