on_delete_event(GdkEventAny *)
{
	if( CheckWorking() )
		return false;
	else
		return true;
}
