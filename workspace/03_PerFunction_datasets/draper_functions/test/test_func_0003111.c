sge_error_iterator_class_create(sge_error_class_t *ec)
{
   sge_error_iterator_class_t* ret = NULL;
   sge_error_iterator_t *elem = NULL;
   sge_error_t *et = (sge_error_t*)ec->sge_error_handle;

   DENTER(TOP_LAYER, "sge_error_message_class_create");

   elem = (sge_error_iterator_t*)sge_malloc(sizeof(sge_error_iterator_t));
   elem->current = et->first;
   elem->is_first_flag = true;

   ret = (sge_error_iterator_class_t*)sge_malloc(sizeof(sge_error_iterator_class_t));
   ret->sge_error_iterator_handle = elem;
   ret->get_message = sge_error_iterator_get_message;
   ret->get_quality = sge_error_iterator_get_quality;
   ret->get_type = sge_error_iterator_get_type;
   ret->next = sge_error_iterator_next;

   DEXIT;
   return ret;
}
