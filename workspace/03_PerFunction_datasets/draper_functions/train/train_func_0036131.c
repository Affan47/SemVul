HPDF_Obj_Free  (HPDF_MMgr    mmgr,
                void         *obj)
{
    HPDF_Obj_Header *header;

    HPDF_PTRACE((" HPDF_Obj_Free\n"));

    if (!obj)
        return;

    header = (HPDF_Obj_Header *)obj;

    if (!(header->obj_id & HPDF_OTYPE_INDIRECT))
        HPDF_Obj_ForceFree (mmgr, obj);
}
