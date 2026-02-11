PasteData (xmlNodePtr node)
{
	xmlNodePtr child;
	string str;
	Object* pObject;
	m_bIsLoading = true;
	EmptyTranslationTable ();
	GtkWidget* w = m_pView->GetWidget ();
	WidgetData* pData = (WidgetData*) g_object_get_data (G_OBJECT (w), "data");
	gcu::Application *app = GetApp ();
	if (!app)
		app = Application::GetApplication ("GChemPaint");
	if (!app)
		return;
	while (node) {
		child = (strcmp ((const char*) node->name, "object"))? node: node->children;
		str = (const char*) child->name;
		pObject = app->CreateObject (str, this);
		if (pObject) {
			AddObject (pObject);
			if (!pObject->Load (child))
				Remove (pObject);
			else {
				m_pView->Update (pObject);
				pData->SetSelected (pObject);
			}
		}
		node = node->next;
	}
	m_bIsLoading = false;
	Loaded ();
	EmptyTranslationTable ();
	FinishOperation ();
}
