get_logger(const ft_string & logger_name)
{
    std::map<ft_string, ft_log *> & all_loggers = get_all_loggers();
    all_loggers_iterator iter = all_loggers.find(logger_name);
    if (iter != all_loggers.end())
        return * iter->second;

    ft_log & parent = get_parent(logger_name);

    return * new ft_log(logger_name, & parent);
}
