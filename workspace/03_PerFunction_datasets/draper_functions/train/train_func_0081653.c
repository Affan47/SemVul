_e_qa_event_border_remove_cb(void *data __UNUSED__, int type __UNUSED__, E_Event_Border_Remove *ev)
{
   E_Quick_Access_Entry *entry;

   entry = _e_qa_entry_find_border(ev->border);
   if (!entry) return ECORE_CALLBACK_RENEW;
   if (entry->transient)
     {
        DBG("closed transient qa border: deleting keybind and entry");
        e_qa_entry_free(entry);
        return ECORE_CALLBACK_RENEW;
     }
   else if (entry->config.relaunch) _e_qa_border_new(entry);
   entry->border = NULL;

   return ECORE_CALLBACK_RENEW;
}
