registerAtom(uint id, void *value)
{
	Atom a(id, NULL);
	if (atoms.contains(&a)) {
		return false;
	}
	assert(value);
	atoms.insert(new Atom(id, value));
	return true;
}
