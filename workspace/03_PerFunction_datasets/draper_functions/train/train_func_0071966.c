addChar(struct String* s, char c){
	if(s == NULL){
		exit(intern);
	}

	if(s->Value == NULL){


		s->Value = (char*)gcMalloc(sizeof(char)*2);

		s->Value[0] = c;
		s->Value[1] = '\0';

		s->Allocated = 2;
		s->Length = 1;


		return True;
	}
	else {

		s->Value = (char*)gcRealloc(s->Value, s->Allocated + 1);
		s->Value[s->Length] = c;
		s->Value[s->Length+1] = '\0';

		s->Allocated += 1;
		s->Length += 1;


		return True;
	}

	Log("String: addChar: neco probehlo spatne", WARNING, STRING);
	return False;
}
