APar_MetaData_atom_QuickInit(short atom_num, const uint32_t atomFlags, uint32_t supplemental_length, uint32_t allotment) {


	parsedAtoms[atom_num].AtomicData = (char*)calloc(1, sizeof(char)* allotment+50 );
	if (parsedAtoms[atom_num].AtomicData == NULL) {
		fprintf(stdout, "AP error: there was insufficient memory available for allocation. Exiting.%c\n", '\a');
		exit(1);
	}

	parsedAtoms[atom_num].AtomicLength = 16 + supplemental_length;
	parsedAtoms[atom_num].AtomicVerFlags = atomFlags;
	parsedAtoms[atom_num].AtomicContainerState = CHILD_ATOM;
	parsedAtoms[atom_num].AtomicClassification = VERSIONED_ATOM;

	return;
}
