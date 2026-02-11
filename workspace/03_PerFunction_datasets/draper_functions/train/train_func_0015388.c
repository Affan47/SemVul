append_end_tag(HSCPRC * hp, HSCTAG * tag) {
   HSCTAG *end_tag;
   DLLIST *taglist = hp->container_stack;

   end_tag = new_hsctag(tag->name);
   if (end_tag) {
      BOOL ok = TRUE;
      DLNODE *nd = NULL;


      end_tag->option = tag->option;


      if ((tag->option & HT_MACRO) && (tag->option & HT_CLOSE))
         ok = copy_local_varlist(end_tag->attr, tag->attr, MCI_APPCTAG);


      end_tag->start_fpos = new_infilepos(hp->inpf);


      if (ok) {
         nd = app_dlnode(taglist, end_tag);
         if (!nd) {
            del_hsctag((APTR) end_tag);
            end_tag = NULL;
         }
      }
   }
   return (end_tag);
}
