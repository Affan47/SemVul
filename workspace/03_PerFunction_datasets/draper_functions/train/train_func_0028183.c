forced_rewrap_line(rfc3676_parser_t handle,
			       int linebreak_opportunity,
			       unicode_char ch,
			       size_t ch_width)
{
	if (linebreak_opportunity != UNICODE_LB_NONE)
	{


		if (handle->nonflowed_line_width
		    + handle->nonflowed_next_word_width
		    > handle->nonflowed_line_target_width)
		{

			emit_rewrapped_line(handle);
		}

		unicode_buf_append_buf(&handle->nonflowed_line,
				       &handle->nonflowed_next_word);

		handle->nonflowed_line_width +=
			handle->nonflowed_next_word_width;
		unicode_buf_clear(&handle->nonflowed_next_word);
		handle->nonflowed_next_word_width=0;
	}


	if (handle->nonflowed_line_width == 0 &&
	    handle->nonflowed_next_word_width + ch_width
	    > handle->nonflowed_line_target_width)
	{
		emit_rewrapped_line(handle);
	}

	unicode_buf_append(&handle->nonflowed_next_word, &ch, 1);
	handle->nonflowed_next_word_width += ch_width;
}
