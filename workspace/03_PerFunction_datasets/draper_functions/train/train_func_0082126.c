r3d_read_header(AVFormatContext *s, AVFormatParameters *ap)
{
    R3DContext *r3d = s->priv_data;
    Atom atom;
    int ret;

    if (read_atom(s, &atom) < 0) {
        av_log(s, AV_LOG_ERROR, "error reading atom\n");
        return -1;
    }
    if (atom.tag == MKTAG('R','E','D','1')) {
        if ((ret = r3d_read_red1(s)) < 0) {
            av_log(s, AV_LOG_ERROR, "error parsing 'red1' atom\n");
            return ret;
        }
    } else {
        av_log(s, AV_LOG_ERROR, "could not find 'red1' atom\n");
        return -1;
    }

    s->data_offset = url_ftell(s->pb);
    dprintf(s, "data offset %#llx\n", s->data_offset);
    if (url_is_streamed(s->pb))
        return 0;

    url_fseek(s->pb, url_fsize(s->pb)-48-8, SEEK_SET);
    if (read_atom(s, &atom) < 0)
        av_log(s, AV_LOG_ERROR, "error reading end atom\n");

    if (atom.tag != MKTAG('R','E','O','B') &&
        atom.tag != MKTAG('R','E','O','F') &&
        atom.tag != MKTAG('R','E','O','S'))
        goto out;

    r3d_read_reos(s);

    if (r3d->rdvo_offset) {
        url_fseek(s->pb, r3d->rdvo_offset, SEEK_SET);
        if (read_atom(s, &atom) < 0)
            av_log(s, AV_LOG_ERROR, "error reading 'rdvo' atom\n");
        if (atom.tag == MKTAG('R','D','V','O')) {
            if (r3d_read_rdvo(s, &atom) < 0)
                av_log(s, AV_LOG_ERROR, "error parsing 'rdvo' atom\n");
        }
    }

 out:
    url_fseek(s->pb, s->data_offset, SEEK_SET);
    return 0;
}
