add_handlers()
{
    add_data_handlers("anno", Handler::OP_READ, &_offset);
    add_data_handlers("value", Handler::OP_READ | Handler::OP_WRITE, &_value);
}
