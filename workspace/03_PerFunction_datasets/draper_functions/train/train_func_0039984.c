setAnimation(char* name){
	alive = true;
	string s(name);
	string nn(this->name);
	s = nn + "-" + s;
	int cur;

	for(cur=0; cur<af->size(); cur++){

		Animation* tmp = (Animation*)(af->getByNumber(cur));
		if(strcmp(tmp->getKnown(),s.c_str()) == 0){
			current = tmp;
			currentframe = 0;
		}
	}
}
