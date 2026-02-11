display_digital_time(GooCanvasItem *item, GcomprisTime *time)
{
  gchar *text = NULL;
  int temps;

  temps = (time->hour+12)*3600 + time->minute*60 + time->second;
  time->hour = (temps / 3600) % 12;
  time->minute = (temps / 60) % 60;
  time->second = temps % 60;

  if(item==NULL)
    return;

  if(gcomprisBoard->level<=2)
    text = g_strdup_printf("%.2d:%.2d", time->hour, time->minute);
  else
    text = g_strdup_printf("%.2d:%.2d:%.2d", time->hour, time->minute, time->second);

  g_object_set (item,
		"text", text,
		NULL);
  g_free(text);

}
