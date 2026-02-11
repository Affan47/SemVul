nssPKIObjectCollection_GetObjects (
  nssPKIObjectCollection *collection,
  nssPKIObject **rvObjects,
  PRUint32 rvSize
)
{
    PRUint32 i = 0;
    PRCList *link = PR_NEXT_LINK(&collection->head);
    pkiObjectCollectionNode *node;
    int error=0;
    while ((i < rvSize) && (link != &collection->head)) {
	node = (pkiObjectCollectionNode *)link;
	if (!node->haveObject) {

	    node->object = (*collection->createObject)(node->object);
	    if (!node->object) {
		link = PR_NEXT_LINK(link);

		nssPKIObjectCollection_RemoveNode(collection,node);
		error++;
		continue;
	    }
	    node->haveObject = PR_TRUE;
	}
	rvObjects[i++] = nssPKIObject_AddRef(node->object);
	link = PR_NEXT_LINK(link);
    }
    if (!error && *rvObjects == NULL) {
	nss_SetError(NSS_ERROR_NOT_FOUND);
    }
    return PR_SUCCESS;
}
