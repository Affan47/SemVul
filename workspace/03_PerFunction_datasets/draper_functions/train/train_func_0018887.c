init_mail_file (i)
     int i;
{
  mailfiles[i]->access_time = mailfiles[i]->mod_time = last_time_mail_checked ? last_time_mail_checked : shell_start_time;
  mailfiles[i]->file_size = 0;
  mailfiles[i]->flags = 0;
}
