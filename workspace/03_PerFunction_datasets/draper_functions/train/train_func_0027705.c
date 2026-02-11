octstr_dump_real(const Octstr *ostr, int level, ...)
{
    va_list p;
    unsigned int loglevel;

    va_start(p, level);
    loglevel = va_arg(p, unsigned int);
    va_end(p);

    switch (loglevel) {
        case GW_DEBUG:
            octstr_dump_debug(ostr, level);
            break;
        case GW_INFO:
            octstr_dump_LOGLEVEL(info, ostr, level);
            break;
        case GW_WARNING:
            octstr_dump_LOGLEVEL(warning, ostr, level);
            break;
        case GW_ERROR:
            octstr_dump_LOGLEVEL(error, ostr, level);
            break;
        default:
            octstr_dump_debug(ostr, level);
            break;
    }
}
