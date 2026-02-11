entry_vattr_size(Slapi_Entry *e)
{
        size_t size = 0;
        Slapi_Vattr *vattr = NULL;

        VATTR_READ_LOCK(e);

        for (vattr = e->e_virtual_attrs; vattr != NULL; vattr = vattr->next) {
                if (vattr->attrname != NULL) {
                        size += strlen(vattr->attrname);
                }
                size += slapi_attrlist_size(vattr->attr);
                size += sizeof(Slapi_Vattr);
        }

        VATTR_READ_UNLOCK(e);
        return (size);
}
