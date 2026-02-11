dump_vid(void) {
   vid_pattern_list *pl;
   int i;

   printf("Vendor ID Pattern List:\n\n");
   printf("Entry\tName\tVendor ID Pattern\n");
   pl = vidlist;
   i=1;
   while (pl != NULL) {
      printf("%d\t%s\t%s\n", i++, pl->name, pl->pattern);
      pl = pl->next;
   }
   printf("\nTotal of %d Vendor ID pattern entries.\n\n", i-1);
}
