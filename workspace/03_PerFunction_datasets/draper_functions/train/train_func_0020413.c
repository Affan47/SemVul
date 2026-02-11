timeval_diff(struct timeval *res, struct timeval *t1, struct timeval *t0)
{
     res->tv_sec = t1->tv_sec - t0->tv_sec;
     res->tv_usec = t1->tv_usec - t0->tv_usec;

     if (res->tv_sec > 0)
     {
          if (res->tv_usec >= 0)
          {
               return 1;
          }
          else
          {
               res->tv_sec -= 1;
               res->tv_usec += 1000000;
               return 1;
          }
     }
     else if (res->tv_sec < 0)
     {
          if (res->tv_usec > 0)
          {
               res->tv_sec += 1;
               res->tv_usec -= 1000000;
               return -1;
          }
          else if (res->tv_usec <= 0);
          {
               return -1;
          }
     }
     else
     {
          if (res->tv_usec > 0)
               return 1;
          else if (res->tv_usec < 0)
               return -1;
          else
               return 0;
     }
}
