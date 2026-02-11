ipmi_check_authentication_capabilities_username (const char *username,
                                                 const char *password,
                                                 fiid_obj_t obj_cmd)
{
  uint8_t authentication_status_anonymous_login;
  uint8_t authentication_status_null_username;
  uint8_t authentication_status_non_null_username;
  uint64_t val;

  if (!fiid_obj_valid (obj_cmd))
    {
      SET_ERRNO (EINVAL);
      return (-1);
    }

  if (FIID_OBJ_TEMPLATE_COMPARE (obj_cmd, tmpl_cmd_get_channel_authentication_capabilities_rs) < 0)
    {
      SET_ERRNO (EINVAL);
      return (-1);
    }

  if (FIID_OBJ_GET (obj_cmd,
                    "authentication_status.anonymous_login",
                    &val) < 0)
    {
      FIID_OBJECT_ERROR_TO_ERRNO (obj_cmd);
      return (-1);
    }
  authentication_status_anonymous_login = val;

  if (FIID_OBJ_GET (obj_cmd,
                    "authentication_status.null_username",
                    &val) < 0)
    {
      FIID_OBJECT_ERROR_TO_ERRNO (obj_cmd);
      return (-1);
    }
  authentication_status_null_username = val;

  if (FIID_OBJ_GET (obj_cmd,
                    "authentication_status.non_null_username",
                    &val) < 0)
    {
      FIID_OBJECT_ERROR_TO_ERRNO (obj_cmd);
      return (-1);
    }
  authentication_status_non_null_username = val;

  if ((!username && !password && !authentication_status_anonymous_login)
      || (!username && password && !authentication_status_null_username)
      || (username  && !authentication_status_non_null_username))
    return (0);

  return (1);
}
