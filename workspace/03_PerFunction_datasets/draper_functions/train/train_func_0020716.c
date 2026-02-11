expand_by_day(struct icalrecur_iterator_impl* impl,short year)
{

    int i;
    pvl_list days_list = pvl_newlist();

    short start_dow, end_dow, end_year_day, start_doy;
    struct icaltimetype tmp = impl->last;

    tmp.year= year;
    tmp.month = 1;
    tmp.day = 1;
    tmp.is_date = 1;

    start_dow = icaltime_day_of_week(tmp);
    start_doy =  icaltime_start_doy_of_week(tmp);


    tmp.year++;
    tmp = icaltime_normalize(tmp);
    tmp.day--;
    tmp = icaltime_normalize(tmp);

    end_dow =  icaltime_day_of_week(tmp);
    end_year_day = icaltime_day_of_year(tmp);

    for(i = 0; BYDAYPTR[i] != ICAL_RECURRENCE_ARRAY_MAX; i++){
        short dow =
            icalrecurrencetype_day_day_of_week(BYDAYPTR[i]);
        short pos =  icalrecurrencetype_day_position(BYDAYPTR[i]);

        if(pos == 0){

            int week;
            for(week = 0; week < 52 ; week ++){
                short doy = start_doy + (week * 7) + dow-1;

                if(doy > end_year_day){
                    break;
                } else {
                    pvl_push(days_list, GINT_TO_POINTER((int)doy));
                }
            }

        } else if ( pos > 0) {
            int first;

            if( dow >= start_dow) {
                first = dow - start_dow + 1;
            } else {
                first = dow - start_dow + 8;
            }

            pvl_push(days_list,GINT_TO_POINTER(first+  (pos-1) * 7));

        } else {
            assert(0);
        }
    }

    return days_list;
}
