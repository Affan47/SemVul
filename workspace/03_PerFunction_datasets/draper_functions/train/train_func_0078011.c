is_year_entry_active(lListElem *tm, lListElem *year_entry, time_t *limit) {
   u_long32 state;
   bool in_yday_range, in_daytime_range = false;

   DENTER(TOP_LAYER, "is_year_entry_active");


   if ((in_yday_range=in_range_list(tm, lGetList(year_entry, CA_yday_range_list), tm_yday_cmp))
     && (in_daytime_range=in_range_list(tm, lGetList(year_entry, CA_daytime_range_list), tm_daytime_cmp))) {
      DPRINTF(("in_range_list(yday) = %d in_range_list(daytime) = %d state = %d\n",
            in_yday_range, in_daytime_range, lGetUlong(year_entry, CA_state)));
      state = lGetUlong(year_entry, CA_state);
   } else {
      DPRINTF(("in_range_list(yday) = %d in_range_list(daytime) = %d\n", in_yday_range, in_daytime_range));
      state = in_daytime_range?QI_DO_ENABLE:0;
   }

   if (limit) {
      bool is_end_of_the_day_reached = false;

      *limit = compute_limit(in_yday_range, in_daytime_range, lGetList(year_entry, CA_yday_range_list), NULL,
            lGetList(year_entry, CA_daytime_range_list), tm, &is_end_of_the_day_reached);

      if (is_end_of_the_day_reached) {
         struct tm *tm_now;
         struct tm res;
         lListElem *new_tm;
         DPRINTF(("trying the next time slot\n"));

         (*limit)++;


         tm_now = localtime_r(limit, &res);


         new_tm= lCreateElem(TM_Type);
         cullify_tm(new_tm, tm_now);

         state = is_year_entry_active(new_tm, year_entry, limit);

         lFreeElem(&new_tm);
      }

   }

   DRETURN(state);
}
