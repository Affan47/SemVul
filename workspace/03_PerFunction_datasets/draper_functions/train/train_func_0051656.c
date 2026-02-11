paste_parse(t, me)
struct token *t;
struct mac_expand *me;
   {
   struct token *t1;
   struct token *trigger = NULL;
   struct tok_lst *lst;
   struct paste_lsts *plst;
   int indx;

   if (me->rest_bdy == NULL || me->rest_bdy->t->tok_id != PpPaste)
      plst = NULL;
   else {


      trigger = copy_t(me->rest_bdy->t);
      me->rest_bdy = me->rest_bdy->next;
      if (me->rest_bdy == NULL)
         errt1(t, "the ## operator must not appear at the end of a macro");
      t1 = me->rest_bdy->t;
      me->rest_bdy = me->rest_bdy->next;


      if (t1->tok_id == '#')
         t1 = stringize(t1, me);
      else
         t1 = copy_t(t1);
      plst = paste_parse(t1, me);
      }


   indx = -1;
   if (t->tok_id == Identifier)
      indx = parm_indx(t->image, me->m);
   if (indx == -1)
      lst = new_t_lst(t);
   else {
      lst = me->args[indx];
      free_t(t);
      }


   if (lst == NULL)
      return plst;
   else
      return new_plsts(trigger, lst, plst);
   }
