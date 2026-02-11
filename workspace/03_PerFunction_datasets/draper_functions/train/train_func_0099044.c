get_cpu_stats(unsigned cpu_index, uint64_t *busy_time, uint64_t *total_time)
{
   char cpuname[32];
   char line[1024];
   FILE *f;

   if (cpu_index == ALL_CPUS)
      strcpy(cpuname, "cpu");
   else
      sprintf(cpuname, "cpu%u", cpu_index);

   f = fopen("/proc/stat", "r");
   if (!f)
      return FALSE;

   while (!feof(f) && fgets(line, sizeof(line), f)) {
      if (strstr(line, cpuname) == line) {
         uint64_t v[12];
         int i, num;

         num = sscanf(line,
                      "%s %"PRIu64" %"PRIu64" %"PRIu64" %"PRIu64" %"PRIu64
                      " %"PRIu64" %"PRIu64" %"PRIu64" %"PRIu64" %"PRIu64
                      " %"PRIu64" %"PRIu64"",
                      cpuname, &v[0], &v[1], &v[2], &v[3], &v[4], &v[5],
                      &v[6], &v[7], &v[8], &v[9], &v[10], &v[11]);
         if (num < 5) {
            fclose(f);
            return FALSE;
         }


         *busy_time = v[0] + v[1] + v[2];
         *total_time = *busy_time;


         for (i = 3; i < num-1; i++) {
            *total_time += v[i];
         }
         fclose(f);
         return TRUE;
      }
   }
   fclose(f);
   return FALSE;
}
