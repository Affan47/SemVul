extedited()
{
	mail::account::resume();

	if (myEdit->from)
		myEdit->from->requestFocus();
	else if (myEdit->to)
		myEdit->to->requestFocus();
	myEdit->message.requestFocus();
}
