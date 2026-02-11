process(int type, char* str)
{
   int genkey = hash(str,strlen(str));
   int id = 0;

   if (topitem == NULL){
      hashnode *newNode = malloc(sizeof(hashnode));
      topitem = newNode;
      newNode->hashcode = genkey;
      newNode->datatype = type;
      newNode->data = malloc(strlen(str) * sizeof(char));
      strcpy(newNode->data,str);
      newNode->nextnode = NULL;
      id = genkey;

   }
   else
   {
      hashnode *travnode = topitem;

      while (travnode->nextnode != NULL )
      {
       if (!strcmp(travnode->data,str))
       {

          id = travnode->hashcode;
          travnode = travnode->nextnode;
       }
       else
          travnode = travnode->nextnode;
      }

      if (id == 0)
      {
         hashnode *newNode = malloc(sizeof(hashnode));
         travnode->nextnode = newNode;
         newNode->hashcode = genkey;
         newNode->datatype = type;
         newNode->data = malloc(strlen(str) * sizeof(char));
         strcpy(newNode->data,str);
         newNode->nextnode = NULL;
         id = genkey;

      }
   }

   return id;
}
