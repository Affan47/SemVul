is_imap_stream(MAILSTREAM *stream)
{
    return(stream && stream->dtb && stream->dtb->name
           && !strcmp(stream->dtb->name, "imap"));
}
