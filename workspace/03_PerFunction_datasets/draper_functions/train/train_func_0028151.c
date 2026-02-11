change_passage(int start,int dir,int newend)


{
  int oldend, i;

  dir--;
  oldend=room[start].path[dir];
  room[start].path[dir]=newend;
  if (newend==0) {
    if (room[oldend-first_room].path[antidir[dir]]==start+first_room)
      room[oldend-first_room].path[antidir[dir]]=0;
    else for(i=0;i<12;i++)
      if (room[oldend-first_room].path[i]==start+first_room)
	{room[oldend-first_room].path[i]=0;break;}
    }
  else
    room[newend-first_room].path[antidir[dir]]=start+first_room;
}
