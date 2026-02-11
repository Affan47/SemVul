clock_proc()
{
     int clock_time=0;
     char buffer[CLOCK];
     char clock[CLOCK]={};
     MsgEnv* msgsend;
	 msgsend = (MsgEnv*)malloc(sizeof(MsgEnv));
     msgsend->type = TIMER_REQUEST;

     MsgEnv* msgdisp;
     msgdisp = (MsgEnv*)malloc(sizeof(MsgEnv));
	 msgdisp->type = DISPLAY_REQUEST;


     K_request_delay(100, WAKE_UP, msgsend);

     while(msgsend->text_area != itoa(WAKE_UP,buffer)){
         msgsend = K_receive_message();
     }

     msgsend = K_receive_message();

     while(msgsend != NULL)
     {


         if(msgsend->type == CLOCK_ON)
         {
             clock_time++;
             K_request_delay(100, WAKE_UP, msgsend);

             while(msgsend->text_area != itoa(WAKE_UP,buffer)){
                  msgsend = K_receive_message();
              }


             clock_time++;
             K_request_delay(100, WAKE_UP, msgsend);
             while(msgsend->text_area != itoa(WAKE_UP,buffer)){
                  msgsend = K_receive_message();
              }
            itoa(clock_time, clock);

         }

         else if(msgsend->type == SET_CLOCK)
         {
              strcpy(clock , "00:00:00");


         }

         msgsend = K_receive_message();
     }

     strcpy(msgdisp->text_area, clock);
     int check;
     check = K_send_console_chars(msgdisp);


}
