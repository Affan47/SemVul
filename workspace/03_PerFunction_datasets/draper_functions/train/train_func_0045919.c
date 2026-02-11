CopyReadLine(CopyState cstate)
{
	bool		result;

	resetStringInfo(&cstate->line_buf);


	cstate->line_buf_converted = false;


	result = CopyReadLineText(cstate);

	if (result)
	{


		if (cstate->copy_dest == COPY_NEW_FE)
		{
			do
			{
				cstate->raw_buf_index = cstate->raw_buf_len;
			} while (CopyLoadRawBuf(cstate));
		}
	}
	else
	{


		switch (cstate->eol_type)
		{
			case EOL_NL:
				Assert(cstate->line_buf.len >= 1);
				Assert(cstate->line_buf.data[cstate->line_buf.len - 1] == '\n');
				cstate->line_buf.len--;
				cstate->line_buf.data[cstate->line_buf.len] = '\0';
				break;
			case EOL_CR:
				Assert(cstate->line_buf.len >= 1);
				Assert(cstate->line_buf.data[cstate->line_buf.len - 1] == '\r');
				cstate->line_buf.len--;
				cstate->line_buf.data[cstate->line_buf.len] = '\0';
				break;
			case EOL_CRNL:
				Assert(cstate->line_buf.len >= 2);
				Assert(cstate->line_buf.data[cstate->line_buf.len - 2] == '\r');
				Assert(cstate->line_buf.data[cstate->line_buf.len - 1] == '\n');
				cstate->line_buf.len -= 2;
				cstate->line_buf.data[cstate->line_buf.len] = '\0';
				break;
			case EOL_UNKNOWN:

				Assert(false);
				break;
		}
	}


	if (cstate->need_transcoding)
	{
		char	   *cvt;

		cvt = pg_client_to_server(cstate->line_buf.data,
								  cstate->line_buf.len);
		if (cvt != cstate->line_buf.data)
		{

			resetStringInfo(&cstate->line_buf);
			appendBinaryStringInfo(&cstate->line_buf, cvt, strlen(cvt));
			pfree(cvt);
		}
	}


	cstate->line_buf_converted = true;

	return result;
}
