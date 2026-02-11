onGlobalEnd(void )
{
	for (list<svutListener*>::iterator it = listeners.begin() ; it != listeners.end() ; ++it)
		(*it)->onGlobalEnd();
}
