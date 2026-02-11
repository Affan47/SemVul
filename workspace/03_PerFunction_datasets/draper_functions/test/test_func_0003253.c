_line_data_reset(Line_Data *st)
{
   if (!st)
     return;

   memset(st, 0, sizeof(Line_Data));
   st->line_angle = ELM_GESTURE_NEGATIVE_ANGLE;
}
