push(stack *s, void*e)
{
  if (s->top >= s->slots)
   {

      s->slots *= 2;
      s->arr = realloc(s->arr, (s->slots*sizeof(void*)));

      if (s->arr == NULL)
      {

          return;
      }
   }

   s->arr[s->top] = e;
   s->top ++;
}
