_val_inc_start(Evas_Object *obj)
{
   ELM_SPINNER_DATA_GET(obj, sd);

   sd->interval = sd->first_interval;
   sd->spin_speed = sd->step;
   if (sd->spin) ecore_timer_del(sd->spin);
   sd->spin = ecore_timer_add(sd->interval, _spin_value, obj);
   _spin_value(obj);
}
