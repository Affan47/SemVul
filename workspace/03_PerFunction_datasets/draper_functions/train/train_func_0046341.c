print_PDBQT( FILE *const logFile,
                  const char *const prefix,
                  const int true_ligand_atoms,
                  const char atomstuff[MAX_ATOMS][MAX_CHARS],
                  const Real crd[MAX_ATOMS][SPACE],
                  const Real charge[MAX_ATOMS],
                  const ParameterEntry parameterArray[MAX_ATOM_TYPES],
                  const int type[MAX_ATOMS],
                  const char *const suffix)
{
    for (int i=0; i<true_ligand_atoms; i++) {
        print_PDBQT_atom_resstr(logFile, prefix,
        i , atomstuff[i], crd,
        1., 0.,
       charge[i], parameterArray[type[i]].autogrid_type, suffix );
    }
    pr( logFile, "\n\n" );
}
