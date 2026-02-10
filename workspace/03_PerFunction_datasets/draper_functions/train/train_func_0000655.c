InitNewLine(char* NewLine, const int ColsPerPage){
		memset( NewLine, ' ', ColsPerPage);
		NewLine[ColsPerPage] = '\0';
		CTermCharAttr DefAttr;	DefAttr.SetToDefault();	DefAttr.SetNeedUpdate(true);
		memset16( GetLineAttr(NewLine, ColsPerPage), DefAttr.AsShort(), ColsPerPage);
}
