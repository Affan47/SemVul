__ecereMethod___ecereNameSpace__ecere__com__BlockPool_Remove(struct __ecereNameSpace__ecere__com__BlockPool * this, struct __ecereNameSpace__ecere__com__MemBlock * block)
{
if(block->prev)
block->prev->next = block->next;
if(block->next)
block->next->prev = block->prev;
if(this->first == block)
this->first = block->next;
if(this->last == block)
this->last = block->prev;
block->next = this->free;
this->free = block;
block->part->blocksUsed--;
this->numBlocks--;
(*block->part->pool).usedSpace -= block->size;
if(!block->part->blocksUsed && this->numBlocks && this->totalSize > this->numBlocks + this->numBlocks / 2)
{
struct __ecereNameSpace__ecere__com__MemBlock * next = this->free, * prev = (((void *)0));
struct __ecereNameSpace__ecere__com__MemPart * part = block->part;

this->free = (((void *)0));
this->totalSize -= part->size;
while(next)
{
if(next->part != part)
{
if(prev)
prev->next = next;
else
this->free = next;
prev = next;
}
next = next->next;
}
;
if(prev)
prev->next = (((void *)0));
__ecereNameSpace__ecere__com__TOTAL_MEM -= part->size * this->blockSpace;
__ecereNameSpace__ecere__com__TOTAL_MEM -= sizeof(struct __ecereNameSpace__ecere__com__MemPart);
this->numParts--;
free(part->memory);
free(part);
}
}
