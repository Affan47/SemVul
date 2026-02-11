_filter_free(Elm_Entry_Markup_Filter *tf)
{
   if (tf->func == elm_entry_filter_limit_size)
     {
        Elm_Entry_Filter_Limit_Size *lim = tf->data;
        if (lim) free(lim);
     }
   else if (tf->func == elm_entry_filter_accept_set)
     {
        Elm_Entry_Filter_Accept_Set *as = tf->data;
        if (as)
          {
             if (as->accepted) eina_stringshare_del(as->accepted);
             if (as->rejected) eina_stringshare_del(as->rejected);
             free(as);
          }
     }
   free(tf);
}
