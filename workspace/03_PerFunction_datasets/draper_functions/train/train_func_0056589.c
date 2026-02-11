cJSONUtils_PatchDetach(cJSON *object,const char *path)
{
	char *parentptr=0,*childptr=0;cJSON *parent=0,*ret=0;

	parentptr=strdup(path);	childptr=strrchr(parentptr,'/');	if (childptr) *childptr++=0;
	parent=cJSONUtils_GetPointer(object,parentptr);
	cJSONUtils_InplaceDecodePointerString(childptr);

	if (!parent) ret=0;
	else if (parent->type==cJSON_Array)		ret=cJSON_DetachItemFromArray(parent,atoi(childptr));
	else if (parent->type==cJSON_Object)	ret=cJSON_DetachItemFromObject(parent,childptr);
	free(parentptr);
	return ret;
}
