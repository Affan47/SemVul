_systray_activate_retry(void *data)
{
   Instance *inst = data;
   Eina_Bool ret;

   fputs("SYSTRAY: reactivate...\n", stderr);
   ret = _systray_activate(inst);
   if (ret)
     fputs("SYSTRAY: activate success!\n", stderr);
   else
     fprintf(stderr, "SYSTRAY: activate failure! retrying in %0.1f seconds\n",
             RETRY_TIMEOUT);

   if (!ret)
     return ECORE_CALLBACK_RENEW;

   inst->timer.retry = NULL;
   return ECORE_CALLBACK_CANCEL;
}
