start_ebml_master(ByteIOContext *pb, unsigned int elementid, uint64_t expectedsize)
{
    int bytes = expectedsize ? ebml_num_size(expectedsize) : 8;
    put_ebml_id(pb, elementid);
    put_ebml_size_unknown(pb, bytes);
    return (ebml_master){ url_ftell(pb), bytes };
}
