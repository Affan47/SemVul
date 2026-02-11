check_identity(char* n,char*m)
{
	int len_n;
	int len_m;
	int i;

	len_n = strlen(n);
	len_m = strlen(m);
	if(len_m != len_n){
		return -1;
	}
	for (i = 0; i < len_n;i++){
		if(n[i] != m[i]){
			return -1;
		}
	}
	return 1;

}
