pretty_print_commit(enum cmit_fmt fmt, const struct commit *commit,
			 struct strbuf *sb,
			 const struct pretty_print_context *context)
{
	unsigned long beginning_of_body;
	int indent = 4;
	const char *msg = commit->buffer;
	char *reencoded;
	const char *encoding;
	int need_8bit_cte = context->need_8bit_cte;

	if (fmt == CMIT_FMT_USERFORMAT) {
		format_commit_message(commit, user_format, sb, context);
		return;
	}

	reencoded = reencode_commit_message(commit, &encoding);
	if (reencoded) {
		msg = reencoded;
	}

	if (fmt == CMIT_FMT_ONELINE || fmt == CMIT_FMT_EMAIL)
		indent = 0;


	if (fmt == CMIT_FMT_EMAIL && need_8bit_cte == 0) {
		int i, ch, in_body;

		for (in_body = i = 0; (ch = msg[i]); i++) {
			if (!in_body) {


				if (ch == '\n' && msg[i+1] == '\n')
					in_body = 1;
			}
			else if (non_ascii(ch)) {
				need_8bit_cte = 1;
				break;
			}
		}
	}

	pp_header(fmt, context->abbrev, context->date_mode, encoding,
		  commit, &msg, sb);
	if (fmt != CMIT_FMT_ONELINE && !context->subject) {
		strbuf_addch(sb, '\n');
	}


	msg = skip_empty_lines(msg);


	if (fmt == CMIT_FMT_ONELINE || fmt == CMIT_FMT_EMAIL)
		pp_title_line(fmt, &msg, sb, context->subject,
			      context->after_subject, encoding, need_8bit_cte);

	beginning_of_body = sb->len;
	if (fmt != CMIT_FMT_ONELINE)
		pp_remainder(fmt, &msg, sb, indent);
	strbuf_rtrim(sb);


	if (fmt != CMIT_FMT_ONELINE)
		strbuf_addch(sb, '\n');


	if (fmt == CMIT_FMT_EMAIL && sb->len <= beginning_of_body)
		strbuf_addch(sb, '\n');

	if (context->show_notes)
		get_commit_notes(commit, sb, encoding,
				 NOTES_SHOW_HEADER | NOTES_INDENT);

	free(reencoded);
}
