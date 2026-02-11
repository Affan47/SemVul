SNSResyncTimeoutThread ()
{
   struct timeval now;
   struct timespec timeout;
   int rc;

   while (1)
   {
      pthread_mutex_lock(&sns_resync_timer);
      gettimeofday(&now, NULL);
      timeout.tv_sec = now.tv_sec + 60;
      timeout.tv_nsec = now.tv_usec * 1000;
      rc = pthread_cond_timedwait(&resync_cond, &sns_resync_timer, &timeout);
      if (rc != ETIMEDOUT)
	perror ("Error in Timeout Request in SNSResyncTimeoutThread");

      pthread_mutex_unlock(&sns_resync_timer);
      if (pauseFlag)
	return (0);
   }

   return (0);
}
