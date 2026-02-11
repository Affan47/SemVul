standard_input(void)
{
        static string_ty *name;
        sub_context_ty  *scp;

        if (!name)
        {
                scp = sub_context_new();
                name = subst_intl(scp, i18n("standard input"));
                sub_context_delete(scp);
        }
        return name;
}
