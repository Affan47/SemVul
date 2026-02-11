Readin(Ainfile *f)
{
	AString *temp, *token;

	temp = f->GetStr();
	token = temp->gettoken();
	type = LookupSkill(token);
	delete token;

	token = temp->gettoken();
	days = token->value();
	delete token;

	exp = 0;
	if(Globals->REQUIRED_EXPERIENCE) {
		token = temp->gettoken();
		exp = token->value();
		delete token;
	}

	delete temp;
}
