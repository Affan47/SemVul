check_bonus_pacman(){
	if(the_bonus!=NULL){
			if((the_bonus->x() < xpos+30) && (the_bonus->x()+30 > xpos) && (the_bonus->y()+30 > ypos) && (the_bonus->y() < ypos+30)){


				switch(the_bonus->type){
					case 'f':	setTimer(200,FREEZE); Mix_PlayChannel(-1,yeah,0); break;
					case 's':	setTimer(200,INVERT); Mix_PlayChannel(-1,uhoh,0); break;
					case 'i':	setTimer(200,INVIS); Mix_PlayChannel(-1,yeah,0); break;
				};
				delete the_bonus;
				the_bonus = NULL;
			}
	}
}
