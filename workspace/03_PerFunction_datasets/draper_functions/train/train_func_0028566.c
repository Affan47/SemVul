UpdateButton(ButtonArray *array, int butnum, char *title, int up)
{
Button *temp;
  temp=find_n(array,butnum);
  if (temp!=NULL) {
    if (title!=NULL) {
      temp->title=(char *)realloc(temp->title,strlen(title)+1);
      strcpy(temp->title,title);
      temp->tw=XTextWidth(ButtonFont,title,strlen(title));
    }
    if (up!=-1) temp->up=up;
  } else return -1;
  temp->needsupdate=1;
  return 1;
}
