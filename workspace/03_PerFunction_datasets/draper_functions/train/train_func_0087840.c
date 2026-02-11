add_handlers()
{
    add_data_handlers("count", Handler::OP_READ, &_count);
    add_data_handlers("limit", Handler::OP_READ, &_limit);
    add_write_handler("limit", writer, h_limit);
    add_data_handlers("active", Handler::OP_READ | Handler::CHECKBOX, &_active);
    add_write_handler("active", writer, h_active);
    add_read_handler("src", reader, h_src);
    add_write_handler("src", writer, h_src);
    add_read_handler("dst", reader, h_dst);
    add_write_handler("dst", writer, h_dst);
    add_read_handler("pausetime", reader, h_pausetime);
    add_write_handler("pausetime", writer, h_pausetime);
    add_write_handler("reset_counts", writer, h_reset_counts);
}
