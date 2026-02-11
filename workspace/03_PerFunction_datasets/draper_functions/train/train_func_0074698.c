attach_pipes (class reader_t *inpipe_,
    class writer_t *outpipe_, const blob_t &peer_identity_)
{

    if (peer_identity_.size ()) {
        xattach_pipes (inpipe_, outpipe_, peer_identity_);
    }
    else {
        blob_t identity (1, 0);
        identity.append (uuid_t ().to_blob (), uuid_t::uuid_blob_len);
        xattach_pipes (inpipe_, outpipe_, identity);
    }
}
