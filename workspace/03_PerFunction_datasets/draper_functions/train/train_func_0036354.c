__ecereMethod___ecereNameSpace__ecere__gfx__drivers__NCursesDisplayDriver_Update(struct __ecereNameSpace__ecere__com__Instance * display, struct __ecereNameSpace__ecere__sys__Box * updateBox)
{
struct __ecereNameSpace__ecere__gfx__drivers__CursesDisplay * cursesDisplay = ((struct __ecereNameSpace__ecere__gfx__Display *)(((char *)display + __ecereClass___ecereNameSpace__ecere__gfx__Display->offset)))->driverData;

curs_set(0);
leaveok(stdscr, (_Bool)1);
wrefresh(stdscr);
if(updateBox == (((void *)0)))
{
cursesDisplay->updateBox.left = ((struct __ecereNameSpace__ecere__gfx__Display *)(((char *)display + __ecereClass___ecereNameSpace__ecere__gfx__Display->offset)))->width;
cursesDisplay->updateBox.top = ((struct __ecereNameSpace__ecere__gfx__Display *)(((char *)display + __ecereClass___ecereNameSpace__ecere__gfx__Display->offset)))->height;
cursesDisplay->updateBox.right = 0;
cursesDisplay->updateBox.bottom = 0;
}
}
