changeSelectedDate(day_win *dw, gint day)
{
    if (day > 0) {
     do {
      orage_move_day(&(dw->startdate), 1);
     } while (--day > 0);
    } else {
     do {
      orage_move_day(&(dw->startdate), -1);
     } while (++day < 0);
    }
}
