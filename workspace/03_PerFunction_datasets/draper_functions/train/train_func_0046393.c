add_handlers()
{
    add_data_handlers("delay", Handler::OP_READ | Handler::OP_WRITE, &_delay, true);
    add_task_handlers(&_task);
}
