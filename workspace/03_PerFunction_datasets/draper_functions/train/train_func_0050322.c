first(void)
{
   void *x;

   x = head;
   down = true;
   while (x) {
      if (left(x)) {
         x = left(x);
         continue;
      }
      return x;
   }

   return NULL;
}
