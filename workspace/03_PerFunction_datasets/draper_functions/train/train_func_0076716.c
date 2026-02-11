get_next_function(chunk_t *pc)
{
   while ((pc = chunk_get_next(pc)) != NULL)
   {
      if ((pc->type == CT_FUNC_DEF) ||
          (pc->type == CT_OC_MSG_DECL) ||
          (pc->type == CT_FUNC_PROTO))
      {
         return(pc);
      }
   }
   return(NULL);
}
