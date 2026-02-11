parse(char *tokens) {
  fortress *fort = malloc(sizeof(fortress));
  fort->dwarf_size = count(tokens, DWARF);
  fort->sub_size = count(tokens, SUB);
  fort->alive = fort->dwarf_size;
  fort->dwarves = malloc(sizeof(dwarf*) * (fort->dwarf_size + fort->sub_size));
  int cur_id = -1;
  int comment = 0;
  int prev_comment = 0;
  dwarf *cur = NULL;

  char token = *tokens;
  int step = 0;
  int c = 0;
  while(token != '\0') {
    #ifdef DEBUG
    printf("Processing Token: %c\n", token);
    #endif

    int temp_prev_comment = prev_comment;
    prev_comment = 0;
    if(token == COMMENT) {
      if(temp_prev_comment) {
        comment ^= 1;
      } else {
        prev_comment = 1;
      }
    }

    if(!comment) {
      switch(token) {
      case DWARF:
      case SUB:
        cur_id++;
        dwarf *cur = malloc(sizeof(dwarf));
        cur->id = cur_id;
        cur->pos = 1;
        int l = inst_len(tokens, c);
        cur->inst_offset = 0;
        cur->dead = (token != DWARF);
        cur->rocks = 0;
        fort->dwarves[cur_id] = cur;

        cur->instructions = malloc(sizeof(char) * l + 1);
        cur->instructions[l] = '\0';

        step = 0;
        break;
      case MINE:
      case WORK:
      case DUMP:
      case LEFT:
      case RIGHT:
        cur->instructions[step] = token;
        step++;
        break;
      }
    }
    c++;
    token = *(tokens + c);
  }
  return fort;
}
