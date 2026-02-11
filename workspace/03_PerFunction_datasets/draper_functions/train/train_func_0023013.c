AddChild  (HPDF_Outline  parent,
           HPDF_Outline  item)
{
    HPDF_Outline first = (HPDF_Outline)HPDF_Dict_GetItem (parent, "First",
                    HPDF_OCLASS_DICT);
    HPDF_Outline last = (HPDF_Outline)HPDF_Dict_GetItem (parent, "Last",
                    HPDF_OCLASS_DICT);
    HPDF_STATUS ret = 0;

    HPDF_PTRACE((" AddChild\n"));

    if (!first)
        ret += HPDF_Dict_Add (parent, "First", item);

    if (last) {
        ret += HPDF_Dict_Add (last, "Next", item);
        ret += HPDF_Dict_Add (item, "Prev", last);
    }

    ret += HPDF_Dict_Add (parent, "Last", item);
    ret += HPDF_Dict_Add (item, "Parent", parent);

    if (ret != HPDF_OK)
        return HPDF_Error_GetCode (item->error);

    return HPDF_OK;
}
