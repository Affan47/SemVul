write(const wchar_t *data, size_t len)
{
    trace(("wide_output::write(this = %08lX, data = %08lX, len = %ld)\n{\n",
        (long)this, (long)data, (long)len));
    assert(data);

    if (buffer_position + len <= buffer_end)
    {
        memcpy(buffer_position, data, len * sizeof(wchar_t));
        buffer_position += len;
    }
    else
    {
        size_t nwc = buffer_position - buffer;
        write_inner(buffer, nwc);
        buffer_position = buffer;

        if (len < buffer_size)
        {
            memcpy(buffer, data, len * sizeof(wchar_t));
            buffer_position += len;
        }
        else
            write_inner(data, len);
    }
    trace(("}\n"));
}
