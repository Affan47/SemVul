createAddress()
{
	if (macho_shared->header.cputype == MACHO_CPU_TYPE_I386) {
		return new AddressX86Flat32();
	} else {
		if (macho_shared->_64) {
			return new AddressFlat64();
		} else {
			return new AddressFlat32();
		}
	}
}
