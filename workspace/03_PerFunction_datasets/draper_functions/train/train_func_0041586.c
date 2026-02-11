ct_Button(char *cp)
{

  AddItem();
  item->type = I_BUTTON;
  AssignDrawTable(item);
  item->header.name = "";
  if (strncasecmp(cp, "restart", 7) == 0)
    item->button.key = IB_RESTART;
  else if (strncasecmp(cp, "quit", 4) == 0)
    item->button.key = IB_QUIT;
  else
    item->button.key = IB_CONTINUE;
  while (!isspace((unsigned char)*cp)) cp++;
  while (isspace((unsigned char)*cp)) cp++;
  if (*cp == '\"') {
    item->button.text = CopyQuotedString(++cp);
    cp += strlen(item->button.text) + 1;
    while (isspace((unsigned char)*cp)) cp++;
  } else
    item->button.text = "";
  if (*cp == '^')
    item->button.keypress = *(++cp) - '@';
  else if (*cp == 'F')
    item->button.keypress = 256 + atoi(++cp);
  else
    item->button.keypress = -1;
  item->button.len = strlen(item->button.text);
  item->header.size_y = item->header.dt_ptr->dt_Ffont->height
     + 2 * TEXT_SPC + 2 * BOX_SPC;
  item->header.size_x = 2 * TEXT_SPC + 2 * BOX_SPC
  + FlocaleTextWidth(item->header.dt_ptr->dt_Ffont, item->button.text,
    item->button.len);
  AddToLine(item);
  cur_button = item;
  myfprintf((stderr,"Created button, fore %s, bg %s, text %s\n",
	     item->header.dt_ptr->dt_color_names[c_item_fg],
	     item->header.dt_ptr->dt_color_names[c_item_bg],
	     item->button.text));
}
