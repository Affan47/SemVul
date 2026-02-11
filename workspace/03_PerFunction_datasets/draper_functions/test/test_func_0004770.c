__ecereMethod___ecereNameSpace__ecere__sys__EARArchive_AddFreeBlock(struct __ecereNameSpace__ecere__com__Instance * this, unsigned int position, unsigned int size)
{
struct __ecereNameSpace__ecere__sys__EARArchive * __ecerePointer___ecereNameSpace__ecere__sys__EARArchive = (struct __ecereNameSpace__ecere__sys__EARArchive *)(this ? (((char *)this) + __ecereClass___ecereNameSpace__ecere__sys__EARArchive->offset) : 0);
struct __ecereNameSpace__ecere__sys__FreeBlock * block, * prevBlock, * nextBlock = (((void *)0));

prevBlock = (((void *)0));
for(block = __ecerePointer___ecereNameSpace__ecere__sys__EARArchive->freeBlocks.first; block; block = block->next)
if(block->end < position)
prevBlock = block;
else
{
nextBlock = block;
break;
}
if(prevBlock && prevBlock->end + 1 == position)
{
prevBlock->end += size;
if(nextBlock && nextBlock->start == prevBlock->end + 1)
{
prevBlock->end = nextBlock->end;
__ecereMethod___ecereNameSpace__ecere__sys__OldList_Delete(&__ecerePointer___ecereNameSpace__ecere__sys__EARArchive->freeBlocks, nextBlock);
}
}
else if(nextBlock && nextBlock->start == position + size)
{
nextBlock->start = position;
}
else
{
__ecereMethod___ecereNameSpace__ecere__sys__OldList_Insert(&__ecerePointer___ecereNameSpace__ecere__sys__EARArchive->freeBlocks, prevBlock, __extension__ ({
struct __ecereNameSpace__ecere__sys__FreeBlock * __ecereInstance1 = __ecereNameSpace__ecere__com__eInstance_New(__ecereClass___ecereNameSpace__ecere__sys__FreeBlock);

__ecereInstance1->start = position, __ecereInstance1->end = position + size - 1, __ecereInstance1;
}));
}
}
