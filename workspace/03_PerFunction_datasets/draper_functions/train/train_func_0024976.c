argf_closed()
{
    next_argv();
    ARGF_FORWARD();
    return rb_io_closed(current_file);
}
