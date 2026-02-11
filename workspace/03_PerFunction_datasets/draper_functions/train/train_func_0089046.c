_MD_CreateFileMap(PRFileMap *fmap, PRInt64 size)
{
    PRFileInfo info;
    PRUint32 sz;

    LL_L2UI(sz, size);
    if (sz) {
        if (PR_GetOpenFileInfo(fmap->fd, &info) == PR_FAILURE) {
            return PR_FAILURE;
        }
        if (sz > info.size) {


            if (fmap->prot != PR_PROT_READWRITE) {
                PR_SetError(PR_NO_ACCESS_RIGHTS_ERROR, 0);
                return PR_FAILURE;
            }
            if (PR_Seek(fmap->fd, sz - 1, PR_SEEK_SET) == -1) {
                return PR_FAILURE;
            }
            if (PR_Write(fmap->fd, "", 1) != 1) {
                return PR_FAILURE;
            }
        }
    }
    if (fmap->prot == PR_PROT_READONLY) {
        fmap->md.prot = PROT_READ;
#ifdef OSF1V4_MAP_PRIVATE_BUG


        fmap->md.flags = MAP_SHARED;
#else
        fmap->md.flags = MAP_PRIVATE;
#endif
    } else if (fmap->prot == PR_PROT_READWRITE) {
        fmap->md.prot = PROT_READ | PROT_WRITE;
        fmap->md.flags = MAP_SHARED;
    } else {
        PR_ASSERT(fmap->prot == PR_PROT_WRITECOPY);
        fmap->md.prot = PROT_READ | PROT_WRITE;
        fmap->md.flags = MAP_PRIVATE;
    }
    return PR_SUCCESS;
}
