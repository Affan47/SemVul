butEnv_events(ButEnv *env)  {
  int  i, selected_fds, fdGroup;
  fd_set  fdSets[3];
  struct timeval  next_timer;
  ButOut  result, temp;

  if (env->dpy)
    butEnv_rcActivate(env);
  for (;;)  {
    result = 0;
    if (env->dpy)  {
      do  {
	XFlush(env->dpy);
	while (XPending(env->dpy))  {
	  result |= handleEvent(env);
	  if (result & BUTOUT_STOPWAIT)
	    return;
	}
	result |= butEnv_checkTimers(env, &next_timer);
	if (result & BUTOUT_STOPWAIT)  {
	  return;
	}
      } while(performQueuedWinStuff(env));
      if (result & BUTOUT_ERR)  {
	XBell(env->dpy, 0);
	result = 0;
      }
    }
    for (fdGroup = 0;  fdGroup < 3;  ++fdGroup)  {
      fdSets[fdGroup] = env->fMasks[fdGroup];
    }
    if (env->dpy && (env->wllen <= env->minWindows))
      return;
    selected_fds = select(env->maxFd, &fdSets[BUT_READFILE],
			  &fdSets[BUT_WRITEFILE],
			  &fdSets[BUT_XFILE], &next_timer);
    assert(selected_fds >= 0);
    if (selected_fds > 0)  {
      for (fdGroup = 0;  fdGroup < 3;  ++fdGroup)  {
	for (i = 0;  i < env->maxGFds[fdGroup];  ++i)  {
	  if (FD_ISSET(i, &fdSets[fdGroup]))  {
	    assert(env->fCallbacks[fdGroup][i].callback != NULL);
	    but_inEvent = TRUE;
	    result |= env->fCallbacks[fdGroup][i].
	      callback(env->fCallbacks[fdGroup][i].packet, i);
	    but_inEvent = FALSE;
	    do  {
	      temp = but_dList(NULL) | butWin_dList(NULL);
	      result |= temp;
	    } while (temp != 0);
	    if (env->dpy)  {
	      butEnv_rcActivate(env);
	      if (result & BUTOUT_ERR)
		XBell(env->dpy, 0);
	    }
	    if (result & BUTOUT_STOPWAIT)  {
	      return;
	    }
	  }
	}
      }
    }
  }
}
