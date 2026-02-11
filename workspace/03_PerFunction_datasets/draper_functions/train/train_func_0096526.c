frame(){

	SDL_Surface* tmp = current->getFrame(currentframe);
	delay--;
	if(delay==0){
		currentframe++;
		delay = delay_set;
	}
	if(currentframe>=current->numframes && current->loop){
		currentframe = 0;
	}
	return tmp;
}
