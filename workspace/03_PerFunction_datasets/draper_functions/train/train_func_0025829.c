BDB_WriteComplexKeyDB(DB *dbp,char *name,int keysize,const void *ptr,int size)

{
DBT *key,*value;
int ret;

key = BDB_NewDBValue(name,keysize);
value = BDB_NewDBValue(ptr,size);

if ((ret = dbp->put(dbp,NULL,key,value,0)) == 0)
   {
   Debug("WriteDB => %s\n",name);

   BDB_DeleteDBValue(key);
   BDB_DeleteDBValue(value);
   return true;
   }
else
   {
   CfOut(cf_error, "",
         "BDB_WriteComplexKeyDB: Error trying to write database: %s\n",
         db_strerror(ret));

   BDB_DeleteDBKey(key);
   BDB_DeleteDBValue(value);
   return false;
   }
}
