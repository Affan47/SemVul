write (string type, int value)
{
	Registry::iterator x = registry.find (type);

	if (x == registry.end()) {
		error << string_compose (_("EnumWriter: unknown enumeration type \"%1\""), type) << endmsg;
		throw unknown_enumeration();
	}

	if (x->second.bitwise) {
		return write_bits (x->second, value);
	} else {
		return write_distinct (x->second, value);
	}
}
