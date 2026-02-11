sftk_DeleteAttribute(SFTKObject *object, SFTKAttribute *attribute)
{
    SFTKSessionObject *sessObject = sftk_narrowToSessionObject(object);

    if (sessObject == NULL) {
	return ;
    }
    PZ_Lock(sessObject->attributeLock);
    if (sftkqueue_is_queued(attribute,attribute->handle,
				sessObject->head, sessObject->hashSize)) {
	sftkqueue_delete(attribute,attribute->handle,
				sessObject->head, sessObject->hashSize);
    }
    PZ_Unlock(sessObject->attributeLock);
}
