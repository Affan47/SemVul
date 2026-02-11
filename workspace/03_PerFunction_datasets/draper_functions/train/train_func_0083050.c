toString() const
{
	string str=inputLines[0][0]->toString()+"_"
			  +inputLines[0][1]->toString()+" "
			  +inputLines[1][0]->toString()+"_"
			  +inputLines[1][1]->toString()+" : ";
	if (isEndPoint()) {
		str+=" endpoint";
	}
	if (isProperVar) {
		str+=" proper";
	}
	if (isCollinear()) {
		str+=" collinear";
	}
	return str;
}
