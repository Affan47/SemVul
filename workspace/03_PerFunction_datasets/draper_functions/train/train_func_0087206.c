send_line_to_child(void )
{
  static char converted_buffer[MAXLINE];
  int converted_num;


  back_it_up(curr_pntr);


  if (buff_pntr)
    insert_queue();


  buff[buff_pntr] = in_buff[num_proc];
  buff_flag[buff_pntr++] = 1;
  buff[buff_pntr] = '\0';
  buff_flag[buff_pntr] = -1;


  converted_num =
    convert_buffer(converted_buffer, buff, buff_flag, buff_pntr);
  write(contNum, converted_buffer, converted_num);


  init_flag(buff_flag, buff_pntr);
  init_buff(buff, buff_pntr);

  buff_pntr = curr_pntr = 0;


  current = NULL;
  num_proc++;
  return;
}
