FindUserByNodeID(int NodeID)
{
   struct avl_traverser avl_trans;
   UserInfo *pUser;

   pUser = (UserInfo *) avl_t_first(&avl_trans,UserTree);
   while(pUser != NULL) {
      if(pUser->NodeID == NodeID) {
         break;
      }
      pUser = (UserInfo *) avl_t_next(&avl_trans);
   }

   return pUser;
}
