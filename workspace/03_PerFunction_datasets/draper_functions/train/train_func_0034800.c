checkpillcollision(){

	int ax = (xpos / SIZET) - 1;
	int ay = (ypos / SIZET) - 1;

	if(lev.map[ax][ay].type=='.'){
		lev.map[ax][ay].type='_';
		score = score + 10;
		Mix_PlayChannel(-1,eatpill,0);
		pillsleft--;

		if(pillsleft==0){


			level++;
			level_free_food();
			if(level>maps.size()){

				endGame();
			} else {

				subgamestate = 1;


				initLevel(level);
				initHannah(7,7);
			}
		}
	} else if(lev.map[ax][ay].type=='p'){
		lev.map[ax][ay].type='_';
		score = score + 100;
		Mix_PlayChannel(-1,eatmagic,0);
		red->timer(pilltime);
		blue->timer(pilltime);
		pink->timer(pilltime);


		red->setAnimation("flash");
		blue->setAnimation("flash");
		pink->setAnimation("flash");
	} else if(lev.map[ax][ay].type=='r'){
		lev.map[ax][ay].type='_';
		openRedDoor();
	}

}
