Create(size_t ElementSize,size_t KeySize)
{
    RedBlackTree *result = CurrentAllocator->malloc(sizeof(RedBlackTree));
    if (result) {
        memset(result,0,sizeof(RedBlackTree));
        result->ElementSize = ElementSize;
        result->VTable = &iRedBlackTree;
        result->Allocator = CurrentAllocator;
    }
    return result;
}
