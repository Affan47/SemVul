pilCdbDumpGrouptoString(PilCdbGroup *db_group, int *n)
{
  PilCdbEntry *db_entry;
  PilCdbValue *db_data;
  char *db_key;
  PilDictionary *entries;
  char **parString;
  int count = 0;


  *n = 0;

  if (!db_group)
    return NULL;


  if (!(entries = pilDictGetData(db_group)) || pilDictIsEmpty(entries))
    return NULL;

  count = 0;
  db_entry = pilDictBegin(entries);
  while (db_entry) {
    db_entry = pilDictNext(entries, db_entry);
    count++;
  }

  parString = (char **)pil_calloc(count, sizeof(char *));

  count = 0;
  db_entry = pilDictBegin(entries);
  while (db_entry) {
    db_key = (char *)pilDictGetKey(db_entry);
    db_data = pilDictGetData(db_entry);


    if (strempty(db_data->value, NULL)) {
      parString[count] = (char *)pil_calloc(strlen(db_key) + 5, sizeof(char));
      sprintf(parString[count], "%s=\"\"", db_key);
    }
    else {
      if (strchr(db_data->value, ' ') || strchr(db_data->value, '\t') ||
          strchr(db_data->value, '\v') || strchr(db_data->value, '\n') ||
          strchr(db_data->value, '\r') || strchr(db_data->value, '\f')) {
        parString[count] = (char *)pil_calloc(strlen(db_key)
                                              + strlen(db_data->value) + 5,
                                              sizeof(char));
        sprintf(parString[count], "%s=\"%s\"", db_key, db_data->value);
      }
      else {
        parString[count] = (char *)pil_calloc(strlen(db_key)
                                              + strlen(db_data->value) + 2,
                                              sizeof(char));
        sprintf(parString[count], "%s=%s", db_key, db_data->value);
      }
    }
    db_entry = pilDictNext(entries, db_entry);
    count++;
  }

  *n = count;

  return parString;

}
