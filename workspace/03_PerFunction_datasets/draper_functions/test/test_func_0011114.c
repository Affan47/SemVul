CClientCompare(const void *avl_a,const void *avl_b,void *avl_param)
{
   ConfClient *p_a = (ConfClient *) avl_a;
   ConfClient *p_b = (ConfClient *) avl_b;

   if(p_a->HisAdr.ADDR == p_b->HisAdr.ADDR) {
      return p_a->HisAdr.PORT - p_b->HisAdr.PORT;
   }

   if(p_a->HisAdr.ADDR > p_b->HisAdr.ADDR) {
      return 1;
   }
   else {
      return -1;
   }
}
