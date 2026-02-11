pass_one(schar bg_typ, schar fg_typ)
{
	int i,j;
	short count, dr;

	for(i=2; i<=WIDTH; i++)
	    for(j=1; j<HEIGHT; j++) {
		for(count=0, dr=0; dr < 8; dr++)
		    if(get_map(i+dirs[dr*2], j+dirs[(dr*2)+1], bg_typ)
								== fg_typ)
			count++;

		switch(count) {
		  case 0 :
		  case 1 :
		  case 2:
			  levl[i][j].typ = bg_typ;
			  break;
		  case 5:
		  case 6:
		  case 7:
		  case 8:
			  levl[i][j].typ = fg_typ;
			  break;
		  default:
			  break;
		  }
	    }
}
