free_block(void *ptr, int kind)
{
    switch (kind) {
    case VM_STRING_UTF:
        JVM_ReleaseUTF(ptr);
        break;
    case VM_MALLOC_BLK:
        free(ptr);
        break;
    }
}
