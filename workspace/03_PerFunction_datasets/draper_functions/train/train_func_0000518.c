fs_binding_get_vals(fs_binding *b, const char *name, int *bound)
{
#ifdef DEBUG_BINDING
    if (!strcmp(DEBUG_BINDING, name)) printf("@@ get_vals("DEBUG_BINDING")\n");
#endif
    int i;

    for (i=0; 1; i++) {
	if (!b[i].name) break;
	if (!strcmp(b[i].name, name)) {
	    if (bound) *bound = b[i].bound;
	    return b[i].vals;
	}
    }


    return NULL;
}
