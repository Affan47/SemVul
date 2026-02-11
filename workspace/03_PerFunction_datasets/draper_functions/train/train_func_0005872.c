cleanup() {
	vector<Block*> bcopy(begin(),end());
	for(vector<Block*>::iterator i=bcopy.begin();i!=bcopy.end();++i) {
		Block *b=*i;
		if(b->deleted) {
			erase(b);
			delete b;
		}
	}
}
