context_rename (CONTEXT_S *context, MAILSTREAM *stream, char *old, char *new)
{
    char tmp[MAILTMPLEN],tmp2[MAILTMPLEN];

    return((context_allowed(context_apply(tmp, context, old, sizeof(tmp)))
	    && context_allowed(context_apply(tmp2, context, new, sizeof(tmp2))))
	     ? pine_mail_rename(stream,tmp,tmp2) : 0L);
}
