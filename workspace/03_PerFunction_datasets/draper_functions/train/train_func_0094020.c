setApplication (const QString & app, const QString & context_name, const QString & context_value )
{
	d->currentElement=0l;
	d->eventList->fill( app.isEmpty() ? KGlobal::mainComponent().componentName()  : app , context_name , context_value );
}
