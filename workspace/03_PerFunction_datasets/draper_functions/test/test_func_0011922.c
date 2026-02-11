find_role_position (const char *role)
{
  int i;

  for (i = 0; ordered_roles[i]; i++)
    {
      if (strcmp (role, ordered_roles[i]) == 0)
        break;
    }

  return i + 1;
}
