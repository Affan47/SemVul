SortJobs()
{
   xarray<Job*> arr;

   ListScan(Job,chain,next)
      arr.append(scan);
   arr.qsort(jobno_compare);

   chain=0;
   int count=arr.count();
   while(count--)
      ListAdd(Job,chain,arr[count],next);

   ListScan(Job,chain,next)
      scan->waiting.qsort(jobno_compare);
}
