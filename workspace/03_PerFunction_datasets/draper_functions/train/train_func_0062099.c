move(){

	int ax = (xpos / SIZET) - 1;
	int ay = (ypos / SIZET) - 1;

	if(!checkcollisions() && xpos==nextxpos && ypos==nextypos){
		direction = nextdir;
			switch(nextdir){
					case 1: nextypos = lev.map[ax][ay-1].t; direction=nextdir; break;
					case 2: nextypos = lev.map[ax][ay+1].t; direction=nextdir; break;
					case 3: nextxpos = lev.map[ax-1][ay].l; direction=nextdir; break;
					case 4: nextxpos = lev.map[ax+1][ay].l; direction=nextdir; break;
			};
	} else if(checkcollisions() && xpos==nextxpos && ypos==nextypos){
		if(nextdir==direction){
			direction = 5;
			nextdir = 5;
		} else if(nextdir!=direction && checknext()){
			direction = 5;
			nextdir=5;
		} else {
			switch(direction){
				case 1: nextypos = lev.map[ax][ay-1].t; break;
				case 2: nextypos = lev.map[ax][ay+1].t; break;
				case 3: nextxpos = lev.map[ax-1][ay].l; break;
				case 4: nextxpos = lev.map[ax+1][ay].l; break;
      };
			direction = direction;
		}
	}

	if(nextxpos!=xpos){
		switch(direction){
			case 3: xpos = xpos - speed; break;
			case 4: xpos = xpos + speed; break;
		};
	} else if(nextypos!=ypos){
		switch(direction){
			case 1: ypos = ypos - speed; break;
			case 2: ypos = ypos + speed; break;
		};
	}

}
