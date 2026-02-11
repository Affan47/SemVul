test_atoms()
{
	uint32_t i;
	atom_t atom;
	atom_manifest_t am1, am2;

	com_start();
	atoms_create(&am1, 100);
	for (i=0; i<240; i++) {
		atom.flags = ATOM_ACTIVE;
		atom.id = i;
		atom.sector = (i >> 3) & 3;
		atom.follow = 0;
		atoms_add(&am1, atom);
	}
	atoms_write(&am1, TMP_ATOM);
	atoms_destroy(&am1);

	atoms_create_from_file(&am2, TMP_ATOM);
	atoms_destroy(&am2);
	com_stop();
}
