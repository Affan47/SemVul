FCEUI_SetCheat(uint32 which, const char *name, int32 a, int32 v, int compare,int s, int type)
{
 struct CHEATF *next=cheats;
 uint32 x=0;

 while(next)
 {
  if(x==which)
  {
   if(name)
   {
    char *t;

    if((t=(char *)realloc(next->name,strlen(name+1))))
    {
     next->name=t;
     strcpy(next->name,name);
    }
    else
     return(0);
   }
   if(a>=0)
    next->addr=a;
   if(v>=0)
    next->val=v;
   if(s>=0)
    next->status=s;
   next->compare=compare;
   next->type=type;

   savecheats=1;
   RebuildSubCheats();

   return(1);
  }
  next=next->next;
  x++;
 }
 return(0);
}
