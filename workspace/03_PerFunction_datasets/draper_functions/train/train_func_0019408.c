ipmi_ek_display_shelf_power_distribution_record(
      struct ipmi_ek_multi_header * record )
{
   int offset = START_DATA_OFFSET;
   unsigned char i,j;
   unsigned char feeds = 0;

   feeds = record->data[offset++];
   printf("   Number of Power Feeds: 0x%02x\n", feeds);

   for (i=0; i<feeds; i++) {
      unsigned char entries;
      unsigned long max_ext = 0;
      unsigned long max_int = 0;
      max_ext = record->data[offset+0] | (record->data[offset+1]<<8);
      printf("   Max External Available Current: %ld Amps\n", (max_ext*10) );

      offset += 2;

      max_int = record->data[offset+0] | (record->data[offset+1]<<8);
      printf("   Max Internal Current:\t   %ld Amps\n", (max_int*10));
      offset += 2;
      printf("   Min Expected Operating Voltage: %d Volts\n",
                     (record->data[offset++]/2));
      entries = record->data[offset++];
      printf("   Feed to FRU count: 0x%02x\n", entries);
      for (j=0; j<entries; j++) {
         printf("\tHW: 0x%02x",   record->data[offset++]);
         printf("\tFRU ID: 0x%02x\n", record->data[offset++]);
      }
   }
}
