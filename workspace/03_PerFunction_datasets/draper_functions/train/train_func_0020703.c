ProgressUpdate(void *effectInstance, double progress)
      {
        if (!effectInstance)
          return kOfxStatErrBadHandle;
        Instance *me = reinterpret_cast<Instance *>(effectInstance);
        bool v = me->progressUpdate(progress);
        return v ? kOfxStatOK : kOfxStatReplyNo;
      }
