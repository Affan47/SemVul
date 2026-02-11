new_history ARGS1((text),
char *text)
{ size_t length;
  int k;

  if ( history_space == NULL )
  { history_space = my_list_calloc(HISTORYSPACE,1,ETERNAL_BLOCK);
    for ( k = 0 ; k < MAXHISTORY ; k++ ) history_offsets[k] = -1;
    history_count = 0;
  }
  length = strlen(text)+1;
  if ( length >= HISTORYSPACE-5 )
  { kb_error(1585,"Command too long to save in history list.\n",WARNING);
    return;
  }
  kb_memmove(history_space+length,history_space,HISTORYSPACE-length);
  for ( k = history_count-1 ; k >= 0 ; k-- )
  {
    history_offsets[k+1] = history_offsets[k] + (int)length;
    if ( history_offsets[k+1] >= HISTORYSPACE )
       { history_offsets[k+1] = -1; history_count--; }
  }
  strcpy(history_space,text);
  history_offsets[0] = 0;
  if ( history_count < MAXHISTORY-1 ) history_count++;
  history_number++;
}
