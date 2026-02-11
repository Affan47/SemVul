fill_group_info (DBusGroupInfo    *info,
                 dbus_gid_t        gid,
                 const DBusString *groupname,
                 DBusError        *error)
{
  const char *group_c_str;

  _dbus_assert (groupname != NULL || gid != DBUS_GID_UNSET);
  _dbus_assert (groupname == NULL || gid == DBUS_GID_UNSET);

  if (groupname)
    group_c_str = _dbus_string_get_const_data (groupname);
  else
    group_c_str = NULL;


#if defined (HAVE_POSIX_GETPWNAM_R) || defined (HAVE_NONPOSIX_GETPWNAM_R)
  {
    struct group *g;
    int result;
    size_t buflen;
    char *buf;
    struct group g_str;
    dbus_bool_t b;


    buflen = sysconf (_SC_GETGR_R_SIZE_MAX);


    if ((long) buflen <= 0)
      buflen = 1024;

    result = -1;
    while (1)
      {
        buf = dbus_malloc (buflen);
        if (buf == NULL)
          {
            dbus_set_error (error, DBUS_ERROR_NO_MEMORY, NULL);
            return FALSE;
          }

        g = NULL;
#ifdef HAVE_POSIX_GETPWNAM_R
        if (group_c_str)
          result = getgrnam_r (group_c_str, &g_str, buf, buflen,
                               &g);
        else
          result = getgrgid_r (gid, &g_str, buf, buflen,
                               &g);
#else
        g = getgrnam_r (group_c_str, &g_str, buf, buflen);
        result = 0;
#endif


        if (result == ERANGE && buflen < 512 * 1024)
          {
            dbus_free (buf);
            buflen *= 2;
          }
        else
          {
            break;
          }
      }

    if (result == 0 && g == &g_str)
      {
        b = fill_user_info_from_group (g, info, error);
        dbus_free (buf);
        return b;
      }
    else
      {
        dbus_set_error (error, _dbus_error_from_errno (errno),
                        "Group %s unknown or failed to look it up\n",
                        group_c_str ? group_c_str : "???");
        dbus_free (buf);
        return FALSE;
      }
  }
#else
  {

    struct group *g;

    g = getgrnam (group_c_str);

    if (g != NULL)
      {
        return fill_user_info_from_group (g, info, error);
      }
    else
      {
        dbus_set_error (error, _dbus_error_from_errno (errno),
                        "Group %s unknown or failed to look it up\n",
                        group_c_str ? group_c_str : "???");
        return FALSE;
      }
  }
#endif
}
