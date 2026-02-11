getObjSense() const
{
   int objSen;
   if(!sym_get_obj_sense(env_, &objSen)){
      return ((double)objSen);
   } else {
      return (0);
   }
}
