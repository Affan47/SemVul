_xdg_mime_magic_read_magic_file(XdgMimeMagic *mime_magic,
                                FILE         *magic_file)
{
    XdgMimeMagicState state;
    XdgMimeMagicMatch *match = NULL;

    state = XDG_MIME_MAGIC_SECTION;

    while (state != XDG_MIME_MAGIC_EOF)
    {
        switch (state)
        {
            case XDG_MIME_MAGIC_SECTION:
                match = _xdg_mime_magic_match_new();
                state = _xdg_mime_magic_parse_header(magic_file, match);
                if (state == XDG_MIME_MAGIC_EOF || state == XDG_MIME_MAGIC_ERROR)
                    _xdg_mime_magic_match_free(match);
                break;
            case XDG_MIME_MAGIC_MAGIC:
                state = _xdg_mime_magic_parse_magic_line(magic_file, match);
                if (state == XDG_MIME_MAGIC_SECTION ||
                        (state == XDG_MIME_MAGIC_EOF && match->mime_type))
                {
                    match->matchlet = _xdg_mime_magic_matchlet_mirror(match->matchlet);
                    _xdg_mime_magic_insert_match(mime_magic, match);
                }
                else if (state == XDG_MIME_MAGIC_EOF || state == XDG_MIME_MAGIC_ERROR)
                    _xdg_mime_magic_match_free(match);
                break;
            case XDG_MIME_MAGIC_ERROR:
                state = _xdg_mime_magic_parse_error(magic_file);
                break;
            case XDG_MIME_MAGIC_EOF:
            default:

                assert(0);
        }
    }
    _xdg_mime_update_mime_magic_extents(mime_magic);
}
