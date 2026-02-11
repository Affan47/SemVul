search_send_stat() {

   double time, speed, cpu;
   sint64 node_nb;

   search_update_current();

   if (DispStat && SearchCurrent->time >= SearchInfo->last_time + 1.0) {

      SearchInfo->last_time = SearchCurrent->time;

      time = SearchCurrent->time;
      speed = SearchCurrent->speed;
      cpu = SearchCurrent->cpu;
      node_nb = SearchCurrent->node_nb;

      send("info time %.0f nodes " S64_FORMAT " nps %.0f cpuload %.0f",time*1000.0,node_nb,speed,cpu*1000.0);

      trans_stats(Trans);
   }
}
