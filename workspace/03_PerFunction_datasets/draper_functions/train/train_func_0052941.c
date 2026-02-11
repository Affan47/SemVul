asc_to_index(char *pnam, struct disk_desc *z) {
    int pnum, pno;

    if (*pnam == '#') {
	pno = atoi(pnam + 1);
    } else {
	pnum = atoi(pnam);
	pno = linux_to_index(pnum, z);
    }
    if (!(pno >= 0 && pno < z->partno))
	fatal(_("%s: no such partition\n"), pnam);
    return pno;
}
