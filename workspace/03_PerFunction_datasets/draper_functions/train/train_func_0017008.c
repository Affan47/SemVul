printlist(const char *msg, EDIT *ep)
{
    long            line;
    char            *blab;

    fprintf(stderr, "%s\n", msg);
    line = 1;
    while (ep)
    {
        blab = "insert";
        if (ep->e_text == NULL)
            blab = "delete";
        if (ep->e_text == &fromsource)
            blab = "source";
        fprintf
        (
            stderr,
            "edit at %08lX: line %ld: %s %ld\n",
            (unsigned long)ep,
            line,
            blab,
            ep->e_count
        );
        if ((ep->e_text == NULL) || (ep->e_text == &fromsource))
            line += ep->e_count;
        ep = ep->e_next;
    }
}
