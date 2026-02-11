PollFalcon( csv_context_t* csv_buffer_list, alarm_context_t* alarm_lines,
                 buffer_t* url_str, st_info_t* st_info,
                 time_t last_csv_time, time_t last_alarm_time)
{
  alarm_line_t* alarm;


  if (!list_empty(alarm_lines))
  {


    alarm = (alarm_line_t*)list_get_at(alarm_lines, list_size(alarm_lines));
    if (alarm) {
      last_alarm_time = alarm->timestamp;
    }
  }


  csv_poll(csv_buffer_list, url_str, st_info, last_csv_time);


  alarm_poll(alarm_lines, url_str, st_info, last_alarm_time);


  alarm_archive(alarm_lines, url_str, st_info);
  if (gDebug) fprintf(stderr,"Alarms Archived.\n");
  csv_archive(csv_buffer_list, url_str, st_info);
  if (gDebug) fprintf(stderr,"CSV Data Archived.\n");


  FlushOpaque();
}
