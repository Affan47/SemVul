CompoundId(char *id)

{ int count = 1;
  char *cid = id;

for (cid = id; *cid != '\0'; cid++)
   {
   if (*cid == '.' || *cid == '|')
      {
      count++;
      }
   }

return(count);
}
