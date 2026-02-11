GetDatabaseAge()
{
CF_DB *dbp;

if (!OpenDB(AVDB,&dbp))
   {
   return;
   }

cf_chmod(AVDB,0644);

if (ReadDB(dbp,"DATABASE_AGE",&AGE,sizeof(double)))
   {
   WAGE = AGE / CF_WEEK * CF_MEASURE_INTERVAL;
   Debug("\n\nPrevious DATABASE_AGE %f\n\n",AGE);
   }
else
   {
   Debug("No previous AGE\n");
   AGE = 0.0;
   }

CloseDB(dbp);
}
