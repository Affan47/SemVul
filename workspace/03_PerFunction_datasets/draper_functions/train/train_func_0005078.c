unpack_calendar_cai_from_ai(struct CategoryAppInfo *cai,
                                       unsigned char *ai_raw, int len)
{

   struct CalendarAppInfo ai;
   int r;
   pi_buffer_t pi_buf;

   jp_logf(JP_LOG_DEBUG, "unpack_calendar_cai_from_ai\n");

   memset(&ai, 0, sizeof(ai));
   pi_buf.data = ai_raw;
   pi_buf.used = len;
   pi_buf.allocated = len;

   r = unpack_CalendarAppInfo(&ai, &pi_buf);
   if ((r <= 0) || (len <= 0)) {
      jp_logf(JP_LOG_DEBUG, "unpack_CalendarAppInfo failed %s %d\n", __FILE__, __LINE__);
      return EXIT_FAILURE;
   }
   memcpy(cai, &(ai.category), sizeof(struct CategoryAppInfo));

   return EXIT_SUCCESS;
}
