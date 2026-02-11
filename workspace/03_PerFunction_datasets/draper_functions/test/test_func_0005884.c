replace(const char *rfrom, const char* rto) {
 if (length() == 0 || rfrom==NULL || strlen(rfrom)==0)
        return *this;
 unsigned int l=strlen(rfrom);
 unsigned int tl= (rto==NULL)?0:strlen(rto);
 make_unique();
 char* p;
 char* dest;
 char* newdest=NULL;
 char* s = my_data->chars;
 if (tl!=l) {
   if (tl>l) {
       GMALLOC(newdest, length()*(tl-l+1)+1);
       }
      else  {
       GMALLOC(newdest, length() + 1);
       }
      dest=newdest;
      if (tl==0) {
           while ((p=strstr(s,rfrom))!=NULL) {

                memcpy(dest,s,p-s);
                dest+=p-s;
                s+=p-s+l;
                }

           strcpy(dest, s);
          }
        else {
          while ((p=strstr(s,rfrom))!=NULL) {
              memcpy(dest,s,p-s);
              dest+=p-s;
              memcpy(dest,rto,tl);
              dest+=tl;
              s+=p-s+l;
              }

          strcpy(dest, s);
          }
       Data* data=new_data(newdest);
       replace_data(data);
       GFREE(newdest);
       }
  else {
    while ((p=strstr(s,rfrom))!=NULL) {
        memcpy(p,rto,l);
        s+=p-s+l;
        }
   }
 return *this;
}
