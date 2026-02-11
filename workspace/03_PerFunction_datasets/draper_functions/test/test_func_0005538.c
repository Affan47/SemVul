strhex_to_int(char *hex){
	int ret = 0;

	while(*hex != 0){
		if((*hex < 'a' || *hex > 'f' ) &&
		   (*hex < 'A' || *hex > 'F' ) &&
		   (*hex < '0' || *hex > '9')){
			return -1;
		}
		ret *= 16;
		ret += hex_conv[(int)*hex];
		hex++;
	}

	return ret;
}
