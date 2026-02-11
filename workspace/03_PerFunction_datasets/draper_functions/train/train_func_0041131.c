Remove (const char* Id)
{
	Object* pObj = GetDescendant (Id);
	if (pObj) {
		pObj->Lock ();
		Remove(pObj);
	}
}
