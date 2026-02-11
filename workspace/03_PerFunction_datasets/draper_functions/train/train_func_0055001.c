readString(char* value){
	string ans = "";
	char temp[200];
	sscanf(value,"%s",temp);
	ans = string(temp);
	return ans;
}
