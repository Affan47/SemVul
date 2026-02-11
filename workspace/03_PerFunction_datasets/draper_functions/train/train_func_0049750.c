form()
{
	if (!_pForm)
		_pForm = new HTMLForm(request(), request().stream());

	return *_pForm;
}
