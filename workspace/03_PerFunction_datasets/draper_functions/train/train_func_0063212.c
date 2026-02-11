send_char(int c)
{
   if(c==TX_START)
   {


      if(transmit_state==TS_INACTIVE)
         transmit_state=TS_TRANSMIT;
      else
      {
         if(transmit_state==TS_TRANSMIT)
            ;
         else
            if(transmit_state==TS_WAITFOREND)
            {
               transmit_state=TS_TRANSMIT;
            }
      }
      start_execute_cmd();
      if(cwmode==0)
      {
         sendpreamble();

         txIold=txInew=0; txQold=txQnew=0;
      }
      else
      {
         txIold=txInew=0; txQold=txQnew=0;
      }
      return 0;
   }
   if( (c==TX_END) || (c==(TX_END|TX_URGENT)) )
   {
      if(c&TX_URGENT)
      {
         txbuf_sta=txbuf_end=txbuf;
      }


      {
         if(sendchar_cwmode==0)
            sendpostamble();
         putcodeword(TX_END);
         transmit_state=TS_WAITFOREND;
      }
   return 0;
   }

   if( (c&TX_MODE) )
   {
      if( c&TXM_TUNE )
         sendchar_cwmode=2;
      else
         if( c&TXM_CW )
            sendchar_cwmode=1;
         else
            sendchar_cwmode=0;
   }

   if(bufferspace()<=128)
      return -1;
   if(c>=0 && c<256)
   {
      if(sendchar_cwmode)
      {
         putcodeword( c|CODE_CW_ECHO );
         send_cw_char(c);
      }
      else
      {
         putcodeword(c|CODE_PLAIN);
      }
   }
   else
      if ((c&TX_FREQ) || (c&TX_MODE))
      {
         putcodeword(c);
      }
   return 0;
}
