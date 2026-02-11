handle_timer()
{
  Bit64u total_emu_time = (bx_pc_system.time_usec()) - s.start_emulated_time;
  Bit64u wanttime = s.lasttime+s.Q;
  Bit64u totaltime = sectousec(time(NULL)) - s.start_time;
  Bit64u thistime=(wanttime>totaltime)?wanttime:totaltime;

#if BX_SLOWDOWN_PRINTF_FEEDBACK
  printf("Entering slowdown timer handler.\n");
#endif


  if(totaltime > total_emu_time) {
    bx_pc_system.deactivate_timer(s.timer_handle);
    bx_pc_system.activate_timer(s.timer_handle,
      (Bit32u)(s.MAXmultiplier * (float)((Bit64s)s.Q)), 0);
#if BX_SLOWDOWN_PRINTF_FEEDBACK
    printf("running at MAX speed\n");
#endif
  } else {
    bx_pc_system.deactivate_timer(s.timer_handle);
    bx_pc_system.activate_timer(s.timer_handle,(Bit32u)s.Q,0);
#if BX_SLOWDOWN_PRINTF_FEEDBACK
    printf("running at NORMAL speed\n");
#endif
  }


  if(wanttime > (totaltime+REALTIME_Q)) {
#if BX_HAVE_USLEEP
    usleep(s.Q);
#elif BX_HAVE_MSLEEP
    msleep(usectomsec((Bit32u)s.Q));
#elif BX_HAVE_SLEEP
    sleep(usectosec(s.Q));
#else
#error do not know have to sleep
#endif


#if BX_SLOWDOWN_PRINTF_FEEDBACK
    printf("DELAYING for a quantum\n");
#endif
  }
  s.lasttime=thistime;


#if 0
  if(wanttime > (totaltime+REALTIME_Q)) {
    if(totaltime > total_emu_time) {
      printf("Solving OpenBSD problem.\n");
    } else {
      printf("too fast.\n");
    }
  } else {
    if(totaltime > total_emu_time) {
      printf("too slow.\n");
    } else {
      printf("sometimes invalid state, normally okay.\n");
    }
  }
#endif
}
