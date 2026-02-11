nssCryptokiObject_Clone (
  nssCryptokiObject *object
)
{
    nssCryptokiObject *rvObject;
    rvObject = nss_ZNEW(NULL, nssCryptokiObject);
    if (rvObject) {
	rvObject->handle = object->handle;
	rvObject->token = nssToken_AddRef(object->token);
	rvObject->isTokenObject = object->isTokenObject;
	if (object->label) {
	    rvObject->label = nssUTF8_Duplicate(object->label, NULL);
	}
    }
    return rvObject;
}
