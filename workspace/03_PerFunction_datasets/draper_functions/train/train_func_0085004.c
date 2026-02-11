TIMING_RESULTS(void)
{
  char buf[200];

#ifdef LOG_TIMERS

#define AILOG_OUT(text, which)                                              \
  fc_snprintf(buf, sizeof(buf), "  %s: %g sec turn, %g sec game", text,     \
              read_timer_seconds(aitimer[which][0]),                        \
              read_timer_seconds(aitimer[which][1]));                       \
  log_test("%s", buf);                                                      \
  notify_conn(NULL, NULL, E_AI_DEBUG, ftc_log, "%s", buf);

  log_test("  --- AI timing results ---");

#else

#define AILOG_OUT(text, which)                                          \
  fc_snprintf(buf, sizeof(buf), "  %s: %g sec turn, %g sec game", text, \
              read_timer_seconds(aitimer[which][0]),                    \
              read_timer_seconds(aitimer[which][1]));                   \
  notify_conn(NULL, NULL, E_AI_DEBUG, ftc_log, "%s", buf);

#endif

  notify_conn(NULL, NULL, E_AI_DEBUG, ftc_log,
              "  --- AI timing results ---");
  AILOG_OUT("Total AI time", AIT_ALL);
  AILOG_OUT("Movemap", AIT_MOVEMAP);
  AILOG_OUT("Units", AIT_UNITS);
  AILOG_OUT(" - Military", AIT_MILITARY);
  AILOG_OUT(" - Attack", AIT_ATTACK);
  AILOG_OUT(" - Defense", AIT_DEFENDERS);
  AILOG_OUT(" - Ferry", AIT_FERRY);
  AILOG_OUT(" - Rampage", AIT_RAMPAGE);
  AILOG_OUT(" - Bodyguard", AIT_BODYGUARD);
  AILOG_OUT(" - Recover", AIT_RECOVER);
  AILOG_OUT(" - Caravan", AIT_CARAVAN);
  AILOG_OUT(" - Hunter", AIT_HUNTER);
  AILOG_OUT(" - Airlift", AIT_AIRLIFT);
  AILOG_OUT(" - Diplomat", AIT_DIPLOMAT);
  AILOG_OUT(" - Air", AIT_AIRUNIT);
  AILOG_OUT(" - Explore", AIT_EXPLORER);
  AILOG_OUT("fstk", AIT_FSTK);
  AILOG_OUT("Settlers", AIT_SETTLERS);
  AILOG_OUT("Workers", AIT_WORKERS);
  AILOG_OUT("Government", AIT_GOVERNMENT);
  AILOG_OUT("Taxes", AIT_TAXES);
  AILOG_OUT("Cities", AIT_CITIES);
  AILOG_OUT(" - Buildings", AIT_BUILDINGS);
  AILOG_OUT(" - Danger", AIT_DANGER);
  AILOG_OUT(" - Worker want", AIT_CITY_TERRAIN);
  AILOG_OUT(" - Military want", AIT_CITY_MILITARY);
  AILOG_OUT(" - Settler want", AIT_CITY_SETTLERS);
  AILOG_OUT("Citizen arrange", AIT_CITIZEN_ARRANGE);
  AILOG_OUT("Tech", AIT_TECH);
}
