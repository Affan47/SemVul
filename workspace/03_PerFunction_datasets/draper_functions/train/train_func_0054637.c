StrError(int errcode)
{
	struct ErrorList *e = UserErrorMessages;
    struct Error *E;
	while (e) {
		if (e->code == errcode)
			return e->Message;
		e = e->Next;
	}
    E = ErrorMessages;
    while (E->code) {
        if (E->code == errcode)
            break;
        E++;
    }
	return E->Message;
}
