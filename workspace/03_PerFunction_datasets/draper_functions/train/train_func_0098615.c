sort_task_by_today ( td1, td2 )
TaskData **td1;
TaskData **td2;
{
  TaskData *tda = *td1;
  TaskData *tdb = *td2;
  int ret = 0;

  if ( tda->last_today_int > tdb->last_today_int )
    ret = 1;
  else if ( tda->last_today_int < tdb->last_today_int )
    ret = -1;
  else if ( tda->last_today_int == tdb->last_today_int )
    ret = ( (void *)tda < (void *)td2 );

  if ( sort_forward )
    return ( - ret );
  else
    return ( ret );
}
