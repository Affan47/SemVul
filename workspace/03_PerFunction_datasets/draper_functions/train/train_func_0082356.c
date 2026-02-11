findFlexTags (void)
{
	tokenInfo *const token = newToken ();
	exception_t exception;

	ClassNames = stringListNew ();
	FunctionNames = stringListNew ();

	exception = (exception_t) (setjmp (Exception));
	while (exception == ExceptionNone)
		parseFlexFile (token);

	stringListDelete (ClassNames);
	stringListDelete (FunctionNames);
	ClassNames = NULL;
	FunctionNames = NULL;
	deleteToken (token);
}
