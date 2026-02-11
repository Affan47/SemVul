fs_binding_clear(fs_binding *b)
{
#ifdef DEBUG_BINDING
    printf("@@ clear()\n");
#endif

    for (int i=0; 1; i++) {
        if (!b[i].name) {
            break;
        }
        b[i].name = NULL;
        b[i].vals->length = 0;
        b[i].bound = 0;
    }
}
