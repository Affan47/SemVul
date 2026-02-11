Set(const char *name,const char *cclosure,const char *cvalue)
{
   const char *msg;

   const ResType *type;

   msg=FindVar(name,&type);
   if(msg)
      return msg;

   xstring_c value(cvalue);
   if(value && type->val_valid && (msg=(*type->val_valid)(&value))!=0)
      return msg;

   xstring_c closure(cclosure);
   if(closure && type->closure_valid && (msg=(*type->closure_valid)(&closure))!=0)
      return msg;

   Resource **scan;

   for(scan=&chain; *scan; scan=&(*scan)->next)
      if((*scan)->type==type
	 && ((closure==0 && (*scan)->closure==0)
	     || (closure && (*scan)->closure
	         && !strcmp((*scan)->closure,closure))))
	 break;


   if(*scan)
   {
      if(value)
	 (*scan)->value.set(value);
      else
      {
	 Resource *to_free=*scan;
	 *scan=(*scan)->next;
	 delete to_free;
      }
      ResClient::ReconfigAll(type->name);
   }
   else
   {
      if(value)
      {
	 chain=new Resource(chain,type,closure,value);
	 ResClient::ReconfigAll(type->name);
      }
   }
   return 0;
}
