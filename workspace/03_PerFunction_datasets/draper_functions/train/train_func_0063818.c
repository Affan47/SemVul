registerWatcher(const std::string &param)
{
    StringMsg *event = new StringMsg(this, "param_changed", param);
    OptionAgent::agent()->addWatcher(param, event);
}
