_e_log_cb(const Eina_Log_Domain *d, Eina_Log_Level level, const char *file, const char *fnc __UNUSED__, int line, const char *fmt, void *data __UNUSED__, va_list args)
{
   const char *color;

   color = eina_log_level_color_get(level);
   fprintf(stdout,
           "%s%s<" EINA_COLOR_RESET "%s%s>" EINA_COLOR_RESET "%s:%d" EINA_COLOR_RESET " ",
           color, _names[level > EINA_LOG_LEVEL_DBG ? EINA_LOG_LEVEL_DBG : level],
           d->domain_str, color, file, line);
   vfprintf(stdout, fmt, args);
   putc('\n', stdout);
}
