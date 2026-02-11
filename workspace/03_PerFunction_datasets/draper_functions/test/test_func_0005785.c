amdlibFree2DArrayWrapping(void **wrappingToFree)
{
    if (wrappingToFree != NULL)
    {
        free((void **)wrappingToFree);
        wrappingToFree = NULL;
    }
}
