dvb_ca_en50221_read_tuple(struct dvb_ca_private *ca, int slot,
				     int *address, int *tupleType, int *tupleLength, u8 * tuple)
{
	int i;
	int _tupleType;
	int _tupleLength;
	int _address = *address;


	if ((_tupleType = ca->pub->read_attribute_mem(ca->pub, slot, _address)) < 0)
		return _tupleType;
	if (_tupleType == 0xff) {
		dprintk("END OF CHAIN TUPLE type:0x%x\n", _tupleType);
		*address += 2;
		*tupleType = _tupleType;
		*tupleLength = 0;
		return 0;
	}
	if ((_tupleLength = ca->pub->read_attribute_mem(ca->pub, slot, _address + 2)) < 0)
		return _tupleLength;
	_address += 4;

	dprintk("TUPLE type:0x%x length:%i\n", _tupleType, _tupleLength);


	for (i = 0; i < _tupleLength; i++) {
		tuple[i] = ca->pub->read_attribute_mem(ca->pub, slot, _address + (i * 2));
		dprintk("  0x%02x: 0x%02x %c\n",
			i, tuple[i] & 0xff,
			((tuple[i] > 31) && (tuple[i] < 127)) ? tuple[i] : '.');
	}
	_address += (_tupleLength * 2);


	*tupleType = _tupleType;
	*tupleLength = _tupleLength;
	*address = _address;
	return 0;
}
