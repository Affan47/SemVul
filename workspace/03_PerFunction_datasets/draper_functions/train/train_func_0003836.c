CopyObject(RedBlackTree *Tree,const void *newObject)
{
    void *tmp = Tree->Allocator->malloc(Tree->ElementSize);
    if (tmp == NULL) {
        Tree->RaiseError("Red/Black tree: Add",CONTAINER_ERROR_NOMEMORY);
        return NULL;
    }
    memcpy(tmp,newObject,Tree->ElementSize);
    return tmp;
}
