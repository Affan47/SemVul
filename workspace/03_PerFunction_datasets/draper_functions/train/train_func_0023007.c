saturate_set(MPL *mpl, SET *set)
{     GADGET *gadget = set->gadget;
      ELEMSET *data;
      MEMBER *elem, *memb;
      TUPLE *tuple, *work[20];
      int i;
      xprintf("Generating %s...\n", set->name);
      eval_whole_set(mpl, gadget->set);

      xassert(gadget->set->array != NULL);
      xassert(gadget->set->array->head != NULL);
      xassert(gadget->set->array->head == gadget->set->array->tail);
      data = gadget->set->array->head->value.set;
      xassert(data->type == A_NONE);
      xassert(data->dim == gadget->set->dimen);

      for (elem = data->head; elem != NULL; elem = elem->next)
      {
         tuple = copy_tuple(mpl, elem->tuple);

         for (i = 0; i < gadget->set->dimen; i++)
            work[i] = NULL;
         for (i = 0; tuple != NULL; tuple = tuple->next)
            work[gadget->ind[i++]-1] = tuple;
         xassert(i == gadget->set->dimen);
         for (i = 0; i < gadget->set->dimen; i++)
         {  xassert(work[i] != NULL);
            work[i]->next = work[i+1];
         }

         if (set->dim == 0)
            tuple = NULL;
         else
            tuple = work[0], work[set->dim-1]->next = NULL;

         memb = find_member(mpl, set->array, tuple);
         if (memb == NULL)
         {

            memb = add_member(mpl, set->array, tuple);
            memb->value.set = create_elemset(mpl, set->dimen);
         }
         else
         {
            delete_tuple(mpl, tuple);
         }

         tuple = work[set->dim];
         xassert(set->dim + set->dimen == gadget->set->dimen);
         work[gadget->set->dimen-1]->next = NULL;


         add_tuple(mpl, memb->value.set, tuple);
      }

      set->data = 1;
      return;
}
