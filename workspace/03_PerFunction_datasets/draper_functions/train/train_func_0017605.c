printbonds(const int natom, const int nbonds[MAX_ATOMS], const int bonded[MAX_ATOMS][MAX_NBONDS], const char *message, const int B_print_all_bonds,
const int outlev, FILE *logFile)
{
    pr(logFile, "%s", message);
    for (int i = 0; i<natom; i++) {
        pr(logFile, "DEBUG:  atom %d  bonded to ", i+1);
        for (int j=0; j<
	    B_print_all_bonds
	    ? MAX_NBONDS
	    : nbonds[i];
	    j++) pr(logFile, "  %d", bonded[i][j]+1);
        pr(logFile, "\n");
    }
}
