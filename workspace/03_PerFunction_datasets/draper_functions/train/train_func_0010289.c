cx_log_fallback_handler(const cxchar *name, cx_log_level_flags level,
                        const cxchar *message, cxptr data)
{

    cxchar prefix[CX_MSG_PREFIX_BUFFER_SIZE];
    cxchar strpid[CX_MSG_FORMAT_UNSIGNED_BUFFER_SIZE];

    cxbool is_fatal = (level & CX_LOG_FLAG_FATAL) != 0;

    cx_file_descriptor fd = cx_msg_format_prefix(prefix, level);


    (void) data;

    if (!message)
        message = "(NULL) message";

    cx_msg_format_unsigned(strpid, getpid(), 10);

    if (name)
        cx_msg_write_string(fd, "\n");
    else
        cx_msg_write_string(fd, "\n**");

    cx_msg_write_string(fd, "(process:");
    cx_msg_write_string(fd, strpid);
    cx_msg_write_string(fd, "): ");

    if (name) {
        cx_msg_write_string(fd, name);
        cx_msg_write_string(fd, "-");
    }

    cx_msg_write_string(fd, prefix);
    cx_msg_write_string(fd, ": ");
    cx_msg_write_string(fd, message);

    if (is_fatal)
        cx_msg_write_string(fd, "\naborting...\n");
    else
        cx_msg_write_string(fd, "\n");

    return;

}
