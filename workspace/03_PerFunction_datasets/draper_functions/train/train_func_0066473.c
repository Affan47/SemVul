append(ft_log_event & event)
{
    const ft_log_level level = event.level;
    if (level < min_level || level > max_level)
        return;

    switch (format) {
        case FC_FMT_DATETIME_LEVEL_CALLER_MSG:
            fprintf(stream, "%s %s [%.*s%s.%s(%d)] ", event.str_now, this_log_label[level],
                    event.file_len, event.file, event.file_suffix, event.function, event.line);
            break;
        case FC_FMT_DATETIME_LEVEL_MSG:
            fprintf(stream, "%s %s ", event.str_now, this_log_label[level]);
            break;
        case FC_FMT_LEVEL_MSG:
            fprintf(stream, "%s ", this_log_label[level]);
            break;
        case FC_FMT_MSG:
        default:

            fprintf(stream, "%s", this_log_label_always[level]);
            break;
    }

    va_list vargs;
    ff_va_copy(vargs, event.vargs);
    vfprintf(stream, event.fmt, vargs);
    va_end(vargs);

    if (event.err != 0) {
        bool is_reported = ff_log_is_reported(event.err);
        fprintf(stream, is_reported ? " (caused by previous error: %s)\n" : ": %s\n", strerror(is_reported ? -event.err : event.err));
    } else
        fputc('\n', stream);
}
