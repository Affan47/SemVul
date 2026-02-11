findGoTags (void)
{
	tokenInfo *const token = newToken ();
	exception_t exception;

	exception = (exception_t) (setjmp (Exception));
	while (exception == ExceptionNone)
		parseGoFile (token);

	deleteToken (token);
	vStringDelete (scope);
	scope = NULL;
}
