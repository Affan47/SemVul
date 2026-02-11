VTGet(in_bc)
cid_recieve_bc in_bc;
{
   space1_t *s ;


   if ((s = findTuple(in_bc.appid, in_bc.name, 0)) != NULL)
      deleteTuple(s) ;
}
