add_handlers()
{
    add_data_handlers("data", Handler::OP_READ | Handler::CALM, &_data);
    add_write_handler("data", change_param, h_data, Handler::RAW);
    add_data_handlers("limit", Handler::OP_READ | Handler::OP_WRITE | Handler::CALM, &_limit);
    add_read_handler("interval", read_param, h_interval, Handler::CALM);
    add_write_handler("interval", change_param, h_interval);
    add_data_handlers("active", Handler::OP_READ | Handler::CALM | Handler::CHECKBOX, &_active);
    add_write_handler("active", change_param, h_active);
    add_data_handlers("count", Handler::OP_READ, &_count);
    add_data_handlers("headroom", Handler::OP_READ | Handler::CALM, &_headroom);
    add_write_handler("headroom", change_param, h_headroom);
    add_write_handler("reset", change_param, h_reset, Handler::BUTTON);
}
