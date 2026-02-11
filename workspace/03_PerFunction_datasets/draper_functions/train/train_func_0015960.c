configure(Vector<String> &conf, ErrorHandler *errh)
{
    _data = String::make_out_of_memory();
    _data_offset = 0;
    String alignment;
    int length_eq = -1, length_ge = -1, length_le = -1;

    if (Args(conf, this, errh)
	.read("DATA", _data)
	.read("DATA_OFFSET", _data_offset)
	.read("LENGTH", length_eq)
	.read("LENGTH_EQ", length_eq)
	.read("LENGTH_GE", length_ge)
	.read("LENGTH_LE", length_le)
	.read("ALIGNMENT", AnyArg(), alignment)
	.complete() < 0)
	return -1;

    if ((length_eq >= 0) + (length_ge >= 0) + (length_le >= 0) > 1)
	return errh->error("specify at most one of LENGTH_EQ, LENGTH_GE, and LENGTH_LE");
    else if (length_eq >= 0)
	_length = length_eq, _length_op = '=';
    else if (length_ge >= 0)
	_length = length_ge - 1, _length_op = '>';
    else if (length_le >= 0)
	_length = length_le + 1, _length_op = '<';
    else
	_length_op = 0;

    _data_op = (_data.out_of_memory() ? 0 : '=');

    if (alignment) {
	if (Args(this, errh).push_back_words(alignment)
	    .read_mp("MODULUS", _alignment_chunk)
	    .read_mp("OFFSET", _alignment_offset)
	    .complete() < 0)
	    return -1;
	else if (_alignment_chunk <= 1 || _alignment_offset < 0 || _alignment_offset >= _alignment_chunk)
	    return errh->error("bad alignment modulus and/or offset");
    }

    return 0;
}
