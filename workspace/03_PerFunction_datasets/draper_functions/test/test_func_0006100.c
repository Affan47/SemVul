dumb_register_sigtype(DUH_SIGTYPE_DESC *desc)
{
	DUH_SIGTYPE_DESC_LINK *desc_link = sigtype_desc;

	ASSERT((desc->load_sigdata && desc->unload_sigdata) || (!desc->load_sigdata && !desc->unload_sigdata));
	ASSERT((desc->start_sigrenderer && desc->end_sigrenderer) || (!desc->start_sigrenderer && !desc->end_sigrenderer));
	ASSERT(desc->sigrenderer_generate_samples && desc->sigrenderer_get_current_sample);

	if (desc_link) {
		do {
			if (desc_link->desc->type == desc->type) {
				desc_link->desc = desc;
				return;
			}
			desc_link = desc_link->next;
		} while (desc_link);
	} else
		dumb_atexit(&destroy_sigtypes);

	desc_link = *sigtype_desc_tail = malloc(sizeof(DUH_SIGTYPE_DESC_LINK));

	if (!desc_link)
		return;

	desc_link->next = NULL;
	sigtype_desc_tail = &desc_link->next;

	desc_link->desc = desc;
}
