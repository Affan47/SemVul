xdr_free_mountlist (mountlist ml)
{
        struct mountbody        *next = NULL;

        if (!ml)
                return;

        while (ml) {
                GF_FREE (ml->ml_hostname);
                GF_FREE (ml->ml_directory);
                next = ml->ml_next;
                GF_FREE (ml);
                ml = next;
        }

        return;
}
