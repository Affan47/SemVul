SetCurrentComment(char* comment)
{
#if DEBUG
 printf("#Comment.c# SetCurrentComment set to <<<%s>>>\n",comment);
#endif

 if(comment)
   {
    if(malloc_comment!=comment)
      {
       malloc_comment=Realloc(malloc_comment,strlen(comment)+1);
       strcpy(malloc_comment,comment);
      }
    current_comment=malloc_comment;
   }
 else
   {
    current_comment=NULL;
    if(malloc_comment) *malloc_comment=0;
   }
}
