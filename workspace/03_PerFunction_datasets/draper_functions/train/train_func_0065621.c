add_object_instance (
  nssPKIObjectCollection *collection,
  nssCryptokiObject *instance,
  PRBool *foundIt
)
{
    PRUint32 i;
    PRStatus status;
    pkiObjectCollectionNode *node;
    nssArenaMark *mark = NULL;
    NSSItem uid[MAX_ITEMS_FOR_UID];
    nsslibc_memset(uid, 0, sizeof uid);


    *foundIt = PR_FALSE;
    node = find_instance_in_collection(collection, instance);
    if (node) {


	nssCryptokiObject_Destroy(instance);
	*foundIt = PR_TRUE;
	return node;
    }
    mark = nssArena_Mark(collection->arena);
    if (!mark) {
	goto loser;
    }
    status = (*collection->getUIDFromInstance)(instance, uid,
                                               collection->arena);
    if (status != PR_SUCCESS) {
	goto loser;
    }


    node = find_object_in_collection(collection, uid);
    if (node) {

	status = nssPKIObject_AddInstance(node->object, instance);
    } else {

	node = nss_ZNEW(collection->arena, pkiObjectCollectionNode);
	if (!node) {
	    goto loser;
	}
	node->object = nssPKIObject_Create(NULL, instance,
	                                   collection->td, collection->cc,
                                           collection->lockType);
	if (!node->object) {
	    goto loser;
	}
	for (i=0; i<MAX_ITEMS_FOR_UID; i++) {
	    node->uid[i] = uid[i];
	}
	node->haveObject = PR_FALSE;
	PR_INIT_CLIST(&node->link);
	PR_INSERT_BEFORE(&node->link, &collection->head);
	collection->size++;
	status = PR_SUCCESS;
    }
    nssArena_Unmark(collection->arena, mark);
    return node;
loser:
    if (mark) {
	nssArena_Release(collection->arena, mark);
    }
    nssCryptokiObject_Destroy(instance);
    return (pkiObjectCollectionNode *)NULL;
}
