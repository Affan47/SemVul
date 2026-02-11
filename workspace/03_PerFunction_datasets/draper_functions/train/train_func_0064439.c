TimeLineGetTime(void *effectInstance, double *time)
      {
        if (!effectInstance)
          return kOfxStatErrBadHandle;
        Instance *me = reinterpret_cast<Instance *>(effectInstance);
        *time = me->timeLineGetTime();
        return kOfxStatOK;
      }
