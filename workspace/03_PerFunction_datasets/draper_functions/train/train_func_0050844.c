mov_read_wide(MOVContext *c, ByteIOContext *pb, MOVAtom atom)
{
    int err;

    if (atom.size < 8)
        return 0;
    if (get_be32(pb) != 0) {
        url_fskip(pb, atom.size - 4);
        return 0;
    }
    atom.type = get_le32(pb);
    atom.offset += 8;
    atom.size -= 8;
    if (atom.type != MKTAG('m','d','a','t')) {
        url_fskip(pb, atom.size);
        return 0;
    }
    err = mov_read_mdat(c, pb, atom);
    return err;
}
