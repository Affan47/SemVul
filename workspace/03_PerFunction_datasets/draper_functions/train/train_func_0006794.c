keypad(void){
  int col;
  int timeout = SCROLL_DELAY;
  char str[6];

  while(alive){
    pthread_mutex_lock(&display_Mutex);
    if(display_flag == CHANGED){
      timeout = 1;
    }

    if(--timeout == 0){
      update_display();
      timeout = SCROLL_DELAY;
    }
    pthread_mutex_unlock(&display_Mutex);

    for(col=0;col<COLS;col++){
      write_to_port(C, 0);
      write_to_port(A, (BYTE) (01 << col));
      write_to_port(C, digits[col]);

      write(fd_RS232,"@00P1?\r",7);
      usleep(SLEEP);
      read(fd_RS232,str,6);

      pthread_mutex_lock(&button_Mutex);
      read_button(col,str[4]);
      pthread_mutex_unlock(&button_Mutex);
    }
  }
  return 0;
}
