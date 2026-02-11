readvalue(Object o,char *id,char *value,Object *out)
{
   struct einfo ei;
   char *set_string;
   int items,shape[MAXRANK],rank;
   Type type;
   Category cat;
   void *p_set;


   ei.maxlen = MSGLEN;
   ei.atend = 0;
   if (value) ei.msgbuf = (char *)DXAllocateZero(ei.maxlen+SLOP);
   if (!ei.msgbuf)
      goto error;
   ei.mp =ei.msgbuf;

      if (!DXExtractString((Object)o,&set_string)){
         if (!DXGetArrayInfo((Array)o,&items,&type,&cat,&rank,shape))
            return ERROR;
         p_set = DXGetArrayData((Array)o);
         if (rank==0) shape[0]=1;
         if (value){
            sprintf(ei.mp, "%s",value); while(*ei.mp) ei.mp++;
	    if (!_dxfprint_message(p_set,&ei,type,rank,shape,items))
	       goto error;
	 }
	 if (out){
            out[0] = (Object)DXNewArrayV(type,CATEGORY_REAL,rank,shape);
            if(!out[0] || !DXAddArrayData((Array)out[0],0,items,(Pointer)p_set))
	       goto error;
	 }
      }
      else{
         shape[0] = (int)strlen(set_string);
         if (value){
            sprintf(ei.mp,"%s",value); while(*ei.mp) ei.mp++;
	    if (!_dxfprint_message(set_string,&ei,TYPE_STRING,1,shape,1))
               goto error;
	 }
	 if (out) out[0] = (Object)DXNewString(set_string);
      }

   if (value) {
      DXUIMessage(id,ei.msgbuf);
      DXFree(ei.msgbuf);
   }
   return OK;

error:
      return ERROR;
}
