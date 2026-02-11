get_subject(THREAD_CONTEXT *context, char *subj)
{
    SUBJECT	**sp;

    decode_rfc1522(subj, context->charset);
    munge_nonprintable(subj);
    subj = eat_re(subj);

    if (!*(sp = subj_hash_find(context->subj_ht, subj, strlen(subj)))) {
	(*sp) = (SUBJECT *)XtMalloc(sizeof(SUBJECT));
	(*sp)->hash_next = NULL;
	(*sp)->next = NULL;
	(*sp)->prev = NULL;
	(*sp)->thread = NULL;
	(*sp)->no_unread = 0;
	(*sp)->disp = 0;
	(*sp)->pixmap = None;
	(*sp)->has_tagged = False;
	(*sp)->subject = XtNewString(subj);
	(*sp)->hash_len = strlen(subj);
	if (context->subjects) {
	    if (!context->last_subj || context->last_subj->next) {

		context->last_subj = context->subjects;
		while (context->last_subj->next)
		    context->last_subj = context->last_subj->next;
	    }

	    (*sp)->prev = context->last_subj;
	    context->last_subj->next = *sp;
	    context->last_subj = *sp;
	} else {
	    context->subjects = *sp;
	    context->last_subj = context->subjects;
	}
    }

    return *sp;
}
