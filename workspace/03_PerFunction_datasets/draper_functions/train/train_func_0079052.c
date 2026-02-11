fillSect4_1 (enGribMeta *en, uShort2 tmplNum, uChar typeEnsemble,
                 uChar perturbNum, uChar numFcsts)
{

   if (tmplNum != 1) {

      return -1;
   }
   if (en->ipdsnum != tmplNum) {

      return -1;
   }
   en->pdsTmpl[15] = typeEnsemble;
   en->pdsTmpl[16] = perturbNum;
   en->pdsTmpl[17] = numFcsts;
   return 37;
}
