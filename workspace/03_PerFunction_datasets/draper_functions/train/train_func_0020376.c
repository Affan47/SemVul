doubleCopyPinFunction(int pin, const QString & argString, void *)
{
	return argString.arg(pin * 2).arg(pin * 2 + 1).arg(pin * 2 + 1).arg(pin * 2 + 2);
}
