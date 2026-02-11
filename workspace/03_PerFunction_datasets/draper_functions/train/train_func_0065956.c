WrapStr(const AString &s)
{
	AString temp;
	for (int i=0; i<wraptab; i++) temp += "  ";
	temp += s;
	AString *temp2 = temp.Trunc(70);
	*file << temp << F_ENDLINE;
	while (temp2) {
		temp = "  ";
		for (int i=0; i<wraptab; i++) temp += "  ";
		temp += *temp2;
		delete temp2;
		temp2 = temp.Trunc(70);
		*file << temp << F_ENDLINE;
	}
}
