_kt_extend_table(KeyTab *kt)
{


  KeySym *newtab = (KeySym *) realloc(kt->table, sizeof(kt->table[0]) *
				      (kt->size + KT_TABLE_INC));


  if(!newtab) {
    _err_record_msg(kt->err, "Can't extend keybinding table", END_ERR_MSG);
    errno = ENOMEM;
    return 1;
  };


  kt->table = newtab;
  kt->size += KT_TABLE_INC;
  return 0;
}
