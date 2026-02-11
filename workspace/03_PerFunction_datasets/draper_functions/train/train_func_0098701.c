parse_tag_buffer(git_tag *tag, const char *buffer, const char *buffer_end)
{
	static const char *tag_types[] = {
		NULL, "commit\n", "tree\n", "blob\n", "tag\n"
	};

	unsigned int i, text_len;
	char *search;
	int error;

	if ((error = git__parse_oid(&tag->target, &buffer, buffer_end, "object ")) < 0)
		return git__rethrow(error, "Failed to parse tag. Object field invalid");

	if (buffer + 5 >= buffer_end)
		return git__throw(GIT_EOBJCORRUPTED, "Failed to parse tag. Object too short");

	if (memcmp(buffer, "type ", 5) != 0)
		return git__throw(GIT_EOBJCORRUPTED, "Failed to parse tag. Type field not found");
	buffer += 5;

	tag->type = GIT_OBJ_BAD;

	for (i = 1; i < ARRAY_SIZE(tag_types); ++i) {
		size_t type_length = strlen(tag_types[i]);

		if (buffer + type_length >= buffer_end)
			return git__throw(GIT_EOBJCORRUPTED, "Failed to parse tag. Object too short");

		if (memcmp(buffer, tag_types[i], type_length) == 0) {
			tag->type = i;
			buffer += type_length;
			break;
		}
	}

	if (tag->type == GIT_OBJ_BAD)
		return git__throw(GIT_EOBJCORRUPTED, "Failed to parse tag. Invalid object type");

	if (buffer + 4 >= buffer_end)
		return git__throw(GIT_EOBJCORRUPTED, "Failed to parse tag. Object too short");

	if (memcmp(buffer, "tag ", 4) != 0)
		return git__throw(GIT_EOBJCORRUPTED, "Failed to parse tag. Tag field not found");

	buffer += 4;

	search = memchr(buffer, '\n', buffer_end - buffer);
	if (search == NULL)
		return git__throw(GIT_EOBJCORRUPTED, "Failed to parse tag. Object too short");

	text_len = search - buffer;

	tag->tag_name = git__malloc(text_len + 1);
	if (tag->tag_name == NULL)
		return GIT_ENOMEM;

	memcpy(tag->tag_name, buffer, text_len);
	tag->tag_name[text_len] = '\0';

	buffer = search + 1;

	tag->tagger = git__malloc(sizeof(git_signature));
	if (tag->tagger == NULL)
		return GIT_ENOMEM;

	if ((error = git_signature__parse(tag->tagger, &buffer, buffer_end, "tagger ")) != 0) {
		free(tag->tag_name);
		git_signature_free(tag->tagger);
		return git__rethrow(error, "Failed to parse tag");
	}

	if( *buffer != '\n' )
		return git__throw(GIT_EOBJCORRUPTED, "Failed to parse tag. No new line before message");

	text_len = buffer_end - ++buffer;

	tag->message = git__malloc(text_len + 1);
	if (tag->message == NULL)
		return GIT_ENOMEM;

	memcpy(tag->message, buffer, text_len);
	tag->message[text_len] = '\0';

	return GIT_SUCCESS;
}
