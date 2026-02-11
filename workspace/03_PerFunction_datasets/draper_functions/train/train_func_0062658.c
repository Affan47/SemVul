elm_progressbar_pulse(Evas_Object *obj,
                      Eina_Bool state)
{
   ELM_PROGRESSBAR_CHECK(obj);
   ELM_PROGRESSBAR_DATA_GET(obj, sd);

   state = !!state;
   if ((!sd->pulse) || (sd->pulse_state == state)) return;

   sd->pulse_state = state;

   if (sd->pulse_state)
     elm_layout_signal_emit(obj, "elm,state,pulse,start", "elm");
   else
     elm_layout_signal_emit(obj, "elm,state,pulse,stop", "elm");
}
