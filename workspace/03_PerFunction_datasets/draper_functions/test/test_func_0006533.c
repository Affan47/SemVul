camel_folder_summary_guess_content_info (CamelMessageInfo *mi,
                                         CamelContentType *ctype)
{
	const CamelMessageContentInfo *ci = camel_message_info_content (mi);

	while (ci) {
		const CamelMessageContentInfo *child = ci;

		do {
			if (child->type && match_content_type (child->type, ctype))
				return child;

			child = child->next;
		} while (child != NULL);

		ci = ci->childs;
	}

	return NULL;
}
