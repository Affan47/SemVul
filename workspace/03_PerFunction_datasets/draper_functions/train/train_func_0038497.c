animationFinished(){


	if(current->numframes == currentframe && !current->loop){
		return true;
	} else {
		return false;
	}
}
