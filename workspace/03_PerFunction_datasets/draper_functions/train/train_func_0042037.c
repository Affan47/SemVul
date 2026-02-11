pilCdbGetInt(const PilCdb *db, const char *group, const char *name,
		 int errval)
{

  PilCdbValue *db_value = pilCdbFindValue((PilCdb *)db, group, name);
  char *last;
  long val;


  if (db_value) {
    val = strtol(db_value->value, &last, 10);


    if (*last == '\0')
      if (INT_MIN <= val && val <= INT_MAX)
	return (int)val;
  }

  return errval;

}
