def_tag_name(HSCPRC * hp, BOOL * start_tag)
{
   STRPTR nw = NULL;
   HSCTAG *tag = NULL;
   DLLIST *taglist = hp->deftag;


   nw = infget_tagid(hp);


   if (nw)
   {
      *start_tag = (BOOL) (strcmp(nw, "/"));
      if (!(*start_tag))
      {

         nw = infget_tagid(hp);
         if (nw)
         {
            tag = find_strtag(taglist, nw);
            if (tag)
            {
               if ((tag->option & HT_CLOSE)
                     ||
                     (tag->option & HT_CONTENT))
               {

                  tag = NULL;
                  hsc_message(hp, MSG_REDEFINE_ENDTAG,
                        "redefined %c", nw);
               }
               else
               {

                  tag->option |= HT_CLOSE;
               }
            }
            else
            {

               tag = NULL;
               hsc_message(hp, MSG_DEFTAG_NO_OPEN,
                     "no start tag for %c", nw);
            }
         }
      }
      else
      {
         tag = find_strtag(taglist, nw);
         if (tag)
         {


            DLNODE *nd = find_dlnode(hp->deftag->first,
                  (APTR) nw, cmp_strtag);


            tag->occured = FALSE;

            hsc_message(hp, MSG_REDEFINE_TAG, "redefined %T", tag);

            del_dlnode(hp->deftag, nd);

         }


         tag = app_tag(taglist, nw);
      }
   }

   return (tag);
}
