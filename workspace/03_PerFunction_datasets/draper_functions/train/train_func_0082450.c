nm_set(int job_field[], int nm)
{
   int i;

   DENTER(TOP_LAYER, "nm_set");


   for (i=0; job_field[i]!=NoName; i++)
      if (job_field[i] == nm) {
         DRETURN_VOID;
      }


   DPRINTF(("%s\n", lNm2Str(nm)));
   job_field[i++] = nm;
   job_field[i] = NoName;

   DRETURN_VOID;
}
