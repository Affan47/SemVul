my_compare(void *item1, void *item2)
{
   sched_pkt *p1 = (sched_pkt *)item1;
   sched_pkt *p2 = (sched_pkt *)item2;
   if (p1->runtime < p2->runtime) {
      return -1;
   } else if (p1->runtime > p2->runtime) {
      return 1;
   }
   if (p1->priority < p2->priority) {
      return -1;
   } else if (p1->priority > p2->priority) {
      return 1;
   }
   return 0;
}
