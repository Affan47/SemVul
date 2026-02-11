native_array_increase_size(CMPIArray * array, CMPICount increment)
{
   struct native_array *a = (struct native_array *) array;

   if ((a->size+increment)>a->max) {
      if (a->size==0) a->max=8;
      else while ((a->size+increment)>a->max) a->max*=2;
      a->data = (struct native_array_item *)
         realloc(a->data, a->max * sizeof(struct native_array_item));
      memset(&a->data[a->size], 0, sizeof(struct native_array_item) * increment);
   }
   a->size += increment;
}
