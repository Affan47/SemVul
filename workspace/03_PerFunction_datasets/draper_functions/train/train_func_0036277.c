__ecereMethod___ecereNameSpace__ecere__sys__EARArchive_SubtractBlock(struct __ecereNameSpace__ecere__com__Instance * this, unsigned int start, unsigned int size)
{
struct __ecereNameSpace__ecere__sys__EARArchive * __ecerePointer___ecereNameSpace__ecere__sys__EARArchive = (struct __ecereNameSpace__ecere__sys__EARArchive *)(this ? (((char *)this) + __ecereClass___ecereNameSpace__ecere__sys__EARArchive->offset) : 0);
struct __ecereNameSpace__ecere__sys__FreeBlock * block;

for(block = __ecerePointer___ecereNameSpace__ecere__sys__EARArchive->freeBlocks.first; block; block = block->next)
{
if(block->end >= start - 1L && block->start <= start + size)
{
if(block->end > start + size && block->start < start - 1L)
{
struct __ecereNameSpace__ecere__sys__FreeBlock * newBlock = (newBlock = __ecereNameSpace__ecere__com__eInstance_New(__ecereClass___ecereNameSpace__ecere__sys__FreeBlock), newBlock->start = start + size, newBlock->end = block->end, newBlock);

block->end = start - 1L;
__ecereMethod___ecereNameSpace__ecere__sys__OldList_Insert(&__ecerePointer___ecereNameSpace__ecere__sys__EARArchive->freeBlocks, block, newBlock);
}
else if(block->end > start + size)
{
block->start = start + size;
}
else if(block->start < start - 1L)
{
block->end = start - 1L;
}
else
{
__ecereMethod___ecereNameSpace__ecere__sys__OldList_Remove(&__ecerePointer___ecereNameSpace__ecere__sys__EARArchive->freeBlocks, block);
((block ? (__ecereClass___ecereNameSpace__ecere__sys__FreeBlock->Destructor ? __ecereClass___ecereNameSpace__ecere__sys__FreeBlock->Destructor(block) : 0, __ecereNameSpace__ecere__com__eSystem_Delete(block)) : 0), block = 0);
}
break;
}
}
}
