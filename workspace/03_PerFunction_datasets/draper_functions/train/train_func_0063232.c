getXmlDescription()
{
	QString s="";
	s+="		<Subgroup>\n";
	s+="		<Name>"+protect(this->name)+"</Name>\n";
	s+="		<Number_of_Students>"+CustomFETString::number(this->numberOfStudents)+"</Number_of_Students>\n";
	s+="		</Subgroup>\n";

	return s;
}
