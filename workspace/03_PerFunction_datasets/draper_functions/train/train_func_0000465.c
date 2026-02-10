write_inner(const wchar_t *data, size_t len)
{
    trace(("wide_output_head::write(this = %08lX, date = %08lX, "
        "len = %ld)\n{\n", (long)this, (long)data, (long)len));
    while (how_many_lines > 0 && len > 0)
    {
        wchar_t wc = *data++;
        --len;

        deeper->put_wc(wc);
        prev_was_newline = (wc == L'\n');
        if (prev_was_newline)
            how_many_lines--;
    }
    trace(("}\n"));
}
