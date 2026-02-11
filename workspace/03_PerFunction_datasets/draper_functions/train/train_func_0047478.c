ff_logl_is_enabled(const char * caller_file, ft_log_level level)
{
    ft_log_event event = {
        "", caller_file, "", "", "",
        0, 0, 0,
        level,

    };
    ff_pretty_file(event);

    ft_string logger_name(event.file, event.file_len);
    ft_log & logger = ft_log::get_logger(logger_name);

    return logger.is_enabled(level);
}
