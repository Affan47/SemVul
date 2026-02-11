item_user_lock_release(User_level_lock *ull)
{
  ull->locked=0;
  ull->thread_id= 0;
  if (--ull->count)
    mysql_cond_signal(&ull->cond);
  else
    delete ull;
}
