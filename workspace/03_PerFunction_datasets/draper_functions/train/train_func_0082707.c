existPadding(unsigned char *block){

int i = block[B_LAST_INDEX];
int a;

		for(a = B_LAST_INDEX; a > (B_LAST_INDEX-i) ; a--){
			if(block[a] == i){
			continue;
		}else{return 0;}
	}
return i;

}
