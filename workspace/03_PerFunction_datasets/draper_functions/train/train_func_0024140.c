_systray_retry(Instance *inst)
{
   if (inst->timer.retry) return;
   inst->timer.retry = ecore_timer_add
       (RETRY_TIMEOUT, _systray_activate_retry, inst);
}
