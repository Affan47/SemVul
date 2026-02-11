fillSect4_8 (enGribMeta *en, uShort2 tmplNum, sInt4 endYear, int endMonth,
                 int endDay, int endHour, int endMin, int endSec,
                 uChar numInterval, sInt4 numMissing,
                 sect4IntervalType * interval)
{
   int j;


   if (tmplNum != 8) {

      return -1;
   }
   if (en->ipdsnum != tmplNum) {

      return -1;
   }
   en->pdsTmpl[15] = endYear;
   en->pdsTmpl[16] = endMonth;
   en->pdsTmpl[17] = endDay;
   en->pdsTmpl[18] = endHour;
   en->pdsTmpl[19] = endMin;
   en->pdsTmpl[20] = endSec;
   en->pdsTmpl[21] = numInterval;
   if (numInterval != 1) {

      return -4;
   }
   en->pdsTmpl[22] = numMissing;
   for (j = 0; j < numInterval; j++) {
      en->pdsTmpl[23] = interval[j].processID;
      en->pdsTmpl[24] = interval[j].incrType;
      en->pdsTmpl[25] = interval[j].timeRangeUnit;
      en->pdsTmpl[26] = interval[j].lenTime;
      en->pdsTmpl[27] = interval[j].incrUnit;
      en->pdsTmpl[28] = interval[j].timeIncr;
   }
   return 58;
}
