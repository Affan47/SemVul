push(void)
{
 if(list==NULL)
   {
    list=(stack*)Malloc(8*sizeof(struct _stack));
    list[0]=first;
    maxdepth=8;
   }
 else if(depth==(maxdepth-1))
   {
    list=Realloc(list,(maxdepth+8)*sizeof(struct _stack));
    maxdepth+=8;
   }

 depth++;
 current=&list[depth];

 reset();
}
