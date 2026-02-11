cr_prop_list_prepend2 (CRPropList * a_this,
                       CRString * a_prop, CRDeclaration * a_decl)
{
        CRPropList *list = NULL,
                *result = NULL;

        g_return_val_if_fail (a_this && PRIVATE (a_this)
                              && a_prop && a_decl, NULL);

        list = cr_prop_list_allocate ();
        g_return_val_if_fail (list, NULL);
        PRIVATE (list)->prop = a_prop;
        PRIVATE (list)->decl = a_decl;
        result = cr_prop_list_prepend (a_this, list);
        return result;
}
