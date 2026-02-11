vcal_manager_copy_attendees(VCalEvent *src, VCalEvent *dest)
{
	GSList *cur = src->answers;
	while (cur && cur->data) {
		Answer *a = (Answer *)cur->data;
		Answer *b = answer_new(a->attendee, a->name, a->answer, a->cutype);
		dest->answers = g_slist_prepend(dest->answers, b);
		cur = cur->next;
	}
	dest->answers = g_slist_reverse(dest->answers);
}
