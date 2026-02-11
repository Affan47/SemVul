processRequest(zhttpd::api::event::Type event, zhttpd::api::IRequest* request, zhttpd::api::IBuffer* buffer)
{
    if (Network::_actions[event - 1] != 0)
    {
        action_t action = Network::_actions[event - 1];
        return (this->*action)(request, buffer);
    }
    return (false);
}
