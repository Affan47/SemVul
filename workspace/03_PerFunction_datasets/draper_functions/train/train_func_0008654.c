extlg_includes_another(Expand_tlg *extlg0, Expand_tlg *extlg1)
{
    List *li1;

    for (li1 = extlg1->tlg_list; li1 != NULL; li1 = li1->next) {
        if (!extlg_includes_tlg(extlg0, li1->data)) {
            return FALSE;
        }
    }

    return TRUE;
}
