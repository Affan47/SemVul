Tk_FindPict(imageName)
    char *imageName;
{
    Tcl_HashEntry *entry;

#ifdef DEBUG
    printf("Tk_FindPict\n");
#endif

    if (!imgPictHashInitialized) {
	return NULL;
    }
    entry = Tcl_FindHashEntry(&imgPictHash, imageName);
    if (entry == NULL) {
	return NULL;
    }
    return (Tk_PictHandle) Tcl_GetHashValue(entry);
}
