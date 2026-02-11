get_undo(int no_of_fields, char* fieldname, char* value)
{
  char * result;
  int i;
  int cmd[] = {
    TRANSACTION_CANCEL,
    TRANSACTION_REMOVE,
    TRANSACTION_REVERSE,
    TRANSACTION_DELETE,
    TRANSACTION_KILL,
    TRANSACTION_UNDO
  };
  for (i=0;i<6;i++) {
    result = get_field_string_from_identifier(cmd[i],no_of_fields,
                                              fieldname, value);
    if (result!=0) break;
  }

  return result;
}
