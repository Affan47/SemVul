check_overlap(nres, dtemp)
int nres;
struct dtemp *dtemp;
{
   int i, j, ires, jres, over;
   long iright, jright, ileft, jleft;

   for (i=0; i < nres; i++)
   {
      ires = dtemp[i].index;
      if (!Results[ires].hit_flag &&
          Results[ires].cumprob * NAlign <= CutoffRepeat)
      {
         over = NO;
         for (j=i+1; j < nres; j++)
         {
            jres = dtemp[j].index;
            if (Results[jres].hit_flag || Results[jres].other_flag)
            {
		ileft = Results[ires].offset;
		jleft = Results[jres].offset;
		iright = Results[ires].offset + Results[ires].width;
		jright = Results[jres].offset + Results[jres].width;
                if (iright > jleft || jright > ileft) over = YES;
            }
         }
         if (!over) Results[ires].other_flag = YES;
      }
   }

}
