write_inner(const wchar_t *data, size_t len)
{


    trace(("wide_output_to_narrow::write_inner(this = %08lX, data = %08lX, "
	"len = %ld)\n{\n", (long)this, (long)data, (long)len));
    while (len > 0)
    {
        char buf[2000];
	language_human();
	size_t buf_pos = 0;
	while (buf_pos + MB_LEN_MAX <= sizeof(buf) && len > 0)
	{
	    trace(("data = %08lX, len = %ld\n", (long)data, (long)len));
	    wchar_t wc = *data++;
	    --len;
	    mbstate_t sequester = state;


	    int n = wcrtomb(buf + buf_pos, wc, &state);
	    if (n == -1)
	    {
                state = sequester;
		language_C();
		deeper->write(buf, buf_pos);
		buf_pos = 0;
		deeper->fprintf("\\x%lX", (unsigned long)wc);
		language_human();
	    }
	    else
		buf_pos += n;
	    prev_was_newline = (wc == L'\n');
	}
	language_C();
	deeper->write(buf, buf_pos);
	buf_pos = 0;
    }
    trace(("}\n"));
}
