attach_set_descr(PostAttachment *pa, char *descr, char *message)
{
    message[0] = '\0';
    XtFree(pa->descr);
    pa->descr = XtNewString(descr);
    return True;
}
