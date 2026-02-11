Problem_5(unsigned a, unsigned b){
    unsigned count = 0;
    unsigned c = a^b;
    while(c!=0){
	if(c&1==1)
	    ++count;
	c>>=1;
    }
    return count;
}
