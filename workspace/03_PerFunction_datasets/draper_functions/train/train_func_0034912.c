trans_set_date(int date) {

   ASSERT(date>=0&&date<DateSize);

   Trans->date = date;

   for (date = 0; date < DateSize; date++) {
      Trans->age[date] = trans_age(date);
   }

   Trans->used = 0;
   Trans->read_nb = 0;
   Trans->read_hit = 0;
   Trans->write_nb = 0;
   Trans->write_hit = 0;
   Trans->write_collision = 0;
}
