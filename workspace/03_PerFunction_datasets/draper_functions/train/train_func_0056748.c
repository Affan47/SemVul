getAtomValue(uint id)
{
	if (id != invalid_atom_id) {
		Atom a(id, NULL);
		Atom *f = (Atom*)atoms.get(atoms.find(&a));
		if (f) return f->value;
	}
	return NULL;
}
