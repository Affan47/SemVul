v_go(int dir)

{
  int newloc, tmploc;
  int i;


  dir--;

  tmploc=loc;
  newloc=room[loc].path[dir];
  if (newloc>exitmsg_base)
    { msgout(newloc-exitmsg_base,1);
      return;}
  if (newloc<0) {
    int v0;

    v0=verb_code(-newloc);
    if (v0==0) {
      if (!PURE_ERROR)
	writeln("GAME ERROR: Invalid verb.");
      return;
    }
    clear_stack();
    (void)scan_metacommand(0,v0,0,0,0,NULL);
    return;
  }
  if (newloc<first_room) {
    if (dir==12)
      sysmsg(182,"Nothing happens.");
    else if (dir==10)
      sysmsg(197,"$You$ can't enter anything here.");
    else if (dir==11)
      sysmsg(198,"$You're$ not inside anything that $you$ can exit.");
    else
      sysmsg(13,"$You$ can't go that way.");
    return;
  }
  if (newloc>maxroom) {
    if (!PURE_ERROR)
      writeln("GAME ERROR: Invalid room number.");
    return;}


  if (dir!=12 && (PURE_HOSTILE || newloc!=oldloc+first_room))
    creatloop(i)
      if (creature[i].location==loc+first_room &&
	  creature[i].hostile) {
	parse_rec tmpcreat;
	curr_creat_rec=&tmpcreat;
	make_parserec(i+first_creat,&tmpcreat);
	sysmsg(14,"$The_c$$c_name$ blocks $your$ way.");
	curr_creat_rec=NULL;
	return;
      }


  goto_room(newloc-first_room);
  if (dir!=12 && newloc!=tmploc+first_room)
    oldloc=tmploc;
  if (dir==12 && special_ptr[loc].size>0)

    runptr(loc,special_ptr,"INTERNAL ERROR: Invalid special ptr",0,NULL,NULL);

  if (tmploc==loc && dir==12)
    do_look=0;
}
