update_line_calcul() {
  int line;
  char str[12];


  if (token_count%2 == 0)
    line = (int)(token_count/2-1);
  else
    line = (int)(token_count/2);

  if(line==-1)
    return;

  sprintf(str, "%d",token_result());
  g_object_set(calcul_line_item[line*2],      "text", BLANK, NULL);
  g_object_set(calcul_line_item_back[line*2], "text", BLANK, NULL);

  if(line < gcomprisBoard->level-1) {
    g_object_set(calcul_line_item[line*2+1],      "text", BLANK, NULL);
    g_object_set(calcul_line_item_back[line*2+1], "text", BLANK, NULL);
  }

}
