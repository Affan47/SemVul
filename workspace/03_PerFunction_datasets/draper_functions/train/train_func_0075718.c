real_city_log(const char *file, const char *function, int line,
                   enum log_level level, bool notify,
                   const struct city *pcity, const char *msg, ...)
{
  char buffer[500];
  char buffer2[500];
  va_list ap;
  char aibuf[500] = "\0";

  CALL_PLR_AI_FUNC(log_fragment_city, city_owner(pcity), aibuf, sizeof(aibuf), pcity);

  fc_snprintf(buffer, sizeof(buffer), "%s %s(%d,%d) [s%d] {%s} ",
              nation_rule_name(nation_of_city(pcity)),
              city_name(pcity),
              TILE_XY(pcity->tile), city_size_get(pcity),
              aibuf);

  va_start(ap, msg);
  fc_vsnprintf(buffer2, sizeof(buffer2), msg, ap);
  va_end(ap);

  cat_snprintf(buffer, sizeof(buffer), "%s", buffer2);
  if (notify) {
    notify_conn(NULL, NULL, E_AI_DEBUG, ftc_log, "%s", buffer);
  }
  do_log(file, function, line, FALSE, level, "%s", buffer);
}
