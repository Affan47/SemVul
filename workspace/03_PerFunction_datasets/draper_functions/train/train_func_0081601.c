attach_pipes (class reader_t *inpipe_,
    class writer_t *outpipe_)
{
    if (inpipe_)
        inpipe_->set_endpoint (this);
    if (outpipe_)
        outpipe_->set_endpoint (this);
    xattach_pipes (inpipe_, outpipe_);
}
