loadFinished(bool ok)
{
	GET_SENDER();
	THIS->progress = 1;
	if (ok)
		GB.Raise(THIS, EVENT_LOAD, 0);
	else
		GB.RaiseLater(THIS, EVENT_ERROR);
}
