japi_allocate_string_vector(int type)
{
   drmaa_attr_values_t *iter;

   if (!(iter = (drmaa_attr_values_t *)malloc(sizeof(drmaa_attr_values_t)))) {
      return NULL;
   }
   iter->iterator_type = type;

   switch (type) {
   case JAPI_ITERATOR_BULK_JOBS:
      iter->it.ji.jobid    = 0;
      iter->it.ji.start    = 0;
      iter->it.ji.end      = 0;
      iter->it.ji.incr     = 0;
      iter->it.ji.next_pos = 0;
      break;
   case JAPI_ITERATOR_STRINGS:
      iter->it.si.strings = NULL;
      iter->it.si.next_pos = NULL;
      break;
   default:
      free(iter);
      iter = NULL;
   }

   return iter;
}
