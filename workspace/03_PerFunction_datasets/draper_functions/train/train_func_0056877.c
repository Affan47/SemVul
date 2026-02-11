Unix_GetCurrentUserName(char *userName, int userNameLen)
{
struct passwd *user_ptr;

memset(userName, 0, userNameLen);
user_ptr = getpwuid(getuid());

if(user_ptr == NULL)
  {
  CfOut(cf_error,"getpwuid","Could not get user name of current process, using \"UNKNOWN\"");
  strncpy(userName, "UNKNOWN", userNameLen - 1);
  return false;
  }

strncpy(userName, user_ptr->pw_name, userNameLen - 1);
return true;
}
