ensure(int chars){

	int pos = out_pos - out_start;

	if (  (pos + chars) >= len ){
		char* newp =(char*)local_malloc(len*2);
		memcpy(newp,out_start,len);
		local_free(out_start);
		out_start = newp;
		out_pos = newp + pos;
		len *=2;
	}
}
