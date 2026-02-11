st_insert(char *id, struct treenode *type, int scope, int function, int array)
{

   int hashid;
   int initial_hashid;
   symtable *newEntry;


   newEntry = (symtable *)malloc(sizeof(symtable));
   if (newEntry)
   {
      newEntry->string = (char *)malloc(strlen(id));
      if (newEntry->string)
      {
         hashid = makeHash(id,strlen(id));


         strcpy(newEntry->string, id);
         newEntry->type = type->val;
         newEntry->scope = scope;
         if (scope == 0)
            newEntry->function = 0;
         else
            newEntry->function = function;
         newEntry->isArray = array;


         if (!symboltable[hashid])
         {

            symboltable[hashid] = newEntry;
         }
         else
         {


            if (!strcmp(symboltable[hashid]->string,id) && (symboltable[hashid]->scope == scope) && (symboltable[hashid]->function == function) && (symboltable[hashid]->isArray == array))
            {


               return hashid;
            }


            initial_hashid = hashid;
            hashid = (hashid + 5) % TABLE_SIZE;

            while (symboltable[hashid] && hashid != initial_hashid){


               if (!strcmp(symboltable[hashid]->string,id) && (symboltable[hashid]->scope == scope) && (symboltable[hashid]->function == function) && (symboltable[hashid]->isArray == array))
               {


                  return hashid;
               }

               hashid = (hashid + 5) % TABLE_SIZE;
            }

            if (initial_hashid == hashid)
            {

               return 0;
            }

            symboltable[hashid] = newEntry;
         }

      }
      else
      {
         yyerror("Memory Allocation Failure - String Allocation");
         return 0;
      }
   }
   else
   {
      yyerror("Memory Allocation Failure - Node Allocations");
      return 0;
   }

   return hashid;

}
