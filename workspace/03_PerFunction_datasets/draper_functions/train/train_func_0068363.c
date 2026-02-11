_dxfcontrol_to_o(Object opmap,Field *opacity)
{
   Map *op;
   int num_op;
   Array c=NULL;
   op = NULL;

   if(opmap){
    if (!DXQueryParameter(opmap,TYPE_FLOAT,2,&num_op)){
      DXSetError(ERROR_INTERNAL,"op map must be 2-vector floats");
      goto error;
    }
    c = DXNewArray(TYPE_FLOAT,CATEGORY_REAL,1,2);
    if (!c)
       return ERROR;
    if (!DXAddArrayData(c,0,num_op,NULL))
       goto error;
    op = (Map *)DXGetArrayData(c);
    if (!DXExtractParameter(opmap,TYPE_FLOAT,2,num_op,(Pointer)op)){
      DXSetError(ERROR_INTERNAL,"can't read op control points");
      goto error;
    }
   }

   *opacity = (Field)_dxfeditor_to_opacity((Array)c);
   if (!*opacity)
      goto error;


   if (!DXSetComponentValue(*opacity,"opacity positions",(Object)c))
      goto error;
   c=NULL;
   if (!DXEndField(*opacity))
      goto error;

   return OK;


error:
   if (c) DXDelete((Object)c);
   return ERROR;
}
