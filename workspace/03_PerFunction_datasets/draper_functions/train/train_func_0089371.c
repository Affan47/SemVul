sd_msg_thread_send_signal(JCR *jcr, int sig)
{
   jcr->lock();
   if (  !jcr->sd_msg_thread_done
       && jcr->SD_msg_chan
       && !pthread_equal(jcr->SD_msg_chan, pthread_self()))
   {
      Dmsg1(800, "Send kill to SD msg chan jid=%d\n", jcr->JobId);
      pthread_kill(jcr->SD_msg_chan, sig);
   }
   jcr->unlock();
}
