ocfreetree(OCtree* tree)
{
    if(tree == NULL) return;
    ocfreenodes(tree->nodes);
    ocfree(tree->constraint);
    ocfree(tree->text);
    if(tree->data.xdrs != NULL) {
        xdr_destroy(tree->data.xdrs);
	ocfree(tree->data.xdrs);
    }
#ifdef OC_DISK_STORAGE
    if(tree->dxdclass == OCDATA) {
	ocfree(tree->data.filename);
        if(tree->data.file != NULL) fclose(tree->data.file);
    }
#else
    ocfree(tree->data.xdrdata);
#endif
    freeocmemdata(tree->data.memdata);
    ocfree(tree);
}
