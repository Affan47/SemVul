UpdateDistributions(char *timekey,struct Averages *av)
{
int position,day,i;
char filename[CF_BUFSIZE];
FILE *fp;


if (IsDefinedClass("Min40_45"))
   {
   day = Day2Number(timekey);

   for (i = 0; i < CF_OBSERVABLES; i++)
      {
      position = CF_GRAINS/2 + (int)(0.5+(CF_THIS[i] - av->Q[i].expect)*CF_GRAINS/(4*sqrt((av->Q[i].var))));

      if (0 <= position && position < CF_GRAINS)
         {
         HISTOGRAM[i][day][position]++;
         }
      }


   snprintf(filename,CF_BUFSIZE,"%s/state/histograms",CFWORKDIR);

   if ((fp = fopen(filename,"w")) == NULL)
      {
      CfOut(cf_error,"fopen","Unable to save histograms");
      return;
      }

   for (position = 0; position < CF_GRAINS; position++)
      {
      fprintf(fp,"%d ",position);

      for (i = 0; i < CF_OBSERVABLES; i++)
         {
         for (day = 0; day < 7; day++)
            {
            fprintf(fp,"%.0lf ",HISTOGRAM[i][day][position]);
            }
         }
      fprintf(fp,"\n");
      }

   fclose(fp);
   }
}
