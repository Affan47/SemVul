getDecimalLiteral(void){
	char ch;
	string result;
	while(pp->getch(ch)){
		if (isdigit(ch)){
			result+=ch;
		}else{
			pp->unget();
			break;
		}
	}
	return result;
}
