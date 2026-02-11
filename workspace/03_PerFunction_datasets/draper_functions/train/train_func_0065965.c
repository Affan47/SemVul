OnSignal (G_GNUC_UNUSED SignalId Signal, G_GNUC_UNUSED Object *Child)
{
	View *view = static_cast < Document * > (GetDocument ())->GetView ();
	gcu::Object *obj;
	std::set < gcu::Object * >::iterator j;
	for (obj = GetFirstLink (j); obj; obj = GetNextLink (j))
		view->Update (obj);
	ResetIndentifiers ();
	return true;
}
