elm_web_dialog_confirm_hook_set(Evas_Object *obj,
                                Elm_Web_Dialog_Confirm func,
                                void *data)
{
   ELM_WEB_CHECK(obj);

#ifdef HAVE_ELEMENTARY_WEB
   ELM_WEB_DATA_GET(obj, sd);

   sd->hook.confirm = func;
   sd->hook.confirm_data = data;
#else
   (void)func;
   (void)data;
#endif
}
