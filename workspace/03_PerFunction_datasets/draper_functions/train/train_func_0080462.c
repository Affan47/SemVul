_dbus_condvar_wait (DBusCondVar *cond,
                    DBusCMutex  *mutex)
{
  if (cond && mutex && thread_init_generation == _dbus_current_generation)
    _dbus_platform_condvar_wait (cond, mutex);
}
