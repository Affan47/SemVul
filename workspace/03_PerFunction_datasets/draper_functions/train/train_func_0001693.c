RemoveElectron (Electron* electron)
{


	electron->SetParent (NULL);
	Update ();

	Document *pDoc = reinterpret_cast<Document*> (GetDocument ());
	if (pDoc)
		pDoc->GetView ()->Update (this);
}
