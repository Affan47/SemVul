read_status() {
   double remaining_time;
   static long last_total_bytes_read=0;
   int diff;

   diff = total_wtmp_bytes_read-last_total_bytes_read;
   if (diff == 0) diff = 1;
   remaining_time=(wtmp_file_size-total_wtmp_bytes_read)*5/(diff);
   last_total_bytes_read=total_wtmp_bytes_read;

   printf("Remaining time: %6.2f seconds\n", remaining_time);


}
