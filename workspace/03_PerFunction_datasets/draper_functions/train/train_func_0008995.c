elm_slideshow_previous(Evas_Object *obj)
{
   char buf[1024];
   Elm_Slideshow_Item *prev = NULL;

   ELM_SLIDESHOW_CHECK(obj);
   ELM_SLIDESHOW_DATA_GET(obj, sd);

   if (sd->current) prev = _item_prev_get(sd->current);

   if ((!prev) || (prev == sd->current)) return;

   _on_slideshow_end(obj, obj, NULL, NULL);

   if (sd->timer) ecore_timer_del(sd->timer);
   sd->timer = NULL;
   if (sd->timeout > 0.0)
     sd->timer = ecore_timer_add(sd->timeout, _timer_cb, obj);

   _item_realize(prev);

   elm_layout_content_set(obj, "elm.swallow.2", VIEW(prev));

   if (!sd->transition)
     sprintf(buf,"none,previous");
   else
     snprintf(buf, 1024, "%s,previous", sd->transition);
   elm_layout_signal_emit(obj, buf, "slideshow");

   sd->previous = sd->current;
   sd->current = prev;
   evas_object_smart_callback_call(obj, SIG_CHANGED, sd->current);
}
