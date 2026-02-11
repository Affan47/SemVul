store_name(LEX *lc, RES_ITEM *item, int index, int pass)
{
   POOLMEM *msg = get_pool_memory(PM_EMSG);
   lex_get_token(lc, T_NAME);
   if (!is_name_valid(lc->str, &msg)) {
      scan_err1(lc, "%s\n", msg);
      return;
   }
   free_pool_memory(msg);

   if (*(item->value)) {
      scan_err2(lc, _("Attempt to redefine name \"%s\" to \"%s\"."),
         *(item->value), lc->str);
      return;
   }
   *(item->value) = bstrdup(lc->str);
   scan_to_eol(lc);
   set_bit(index, res_all.hdr.item_present);
}
