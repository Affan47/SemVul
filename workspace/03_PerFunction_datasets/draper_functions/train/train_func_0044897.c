searchCriteriaRequireOnlyImageHeaderLoaded(struct AISLib_SearchCriteria * criteria)
{
   if (criteria->colorRangeUsed) { return 0; }
   if (criteria->similarityUsed) { return 0; }
   if (criteria->containsUsed) { return 0; }
   if ( (criteria->minFacesUsed)||(criteria->maxFacesUsed) ) { return 0; }
   return 1;
}
