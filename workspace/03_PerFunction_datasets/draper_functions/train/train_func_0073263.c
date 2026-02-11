look_room(void)
{
  compute_seen();
  writeln("");
  if (islit()) {
    if (room[loc].name!=NULL && room[loc].name[0]!=0 &&
	(!PURE_ROOMTITLE) )
      {
	agt_textcolor(-1);
	writestr(room[loc].name);
	agt_textcolor(-2);
	writeln("");
      }
    if (room_firstdesc && room[loc].initdesc!=0)
      msgout(room[loc].initdesc,1);
    else if (room_ptr[loc].size>0)
      print_descr(room_ptr[loc],1);
    print_contents(loc+first_room,1);
    if (listexit_flag)
      v_listexit();
  }
  else
    sysmsg( room[loc].light==1?6:7,
	    "It is dark. $You$ can't see anything.");
  room_firstdesc=0;
  do_look=0;
}
