end_ebml_master(ByteIOContext *pb, ebml_master master)
{
    int64_t pos = url_ftell(pb);


    if (url_is_streamed(pb))
        return;

    url_fseek(pb, master.pos - master.sizebytes, SEEK_SET);
    put_ebml_num(pb, pos - master.pos, master.sizebytes);
    url_fseek(pb, pos, SEEK_SET);
}
