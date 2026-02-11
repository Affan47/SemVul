SafeMallocString(char* x,char* file,int line)
{
 char* t=NULL;

 if(x)
   {
    t=(char*)SafeMalloc(strlen(x)+1,file,line);
    strcpy(t,x);
   }

 return(t);
}
