atoms_close(void)
{
	uint i;

	for (i = 0; i < G_N_ELEMENTS(atoms); i++) {
		table_desc_t *td = &atoms[i];

		htable_foreach(td->table, atom_warn_free, td);
		htable_free_null(&td->table);
	}
}
