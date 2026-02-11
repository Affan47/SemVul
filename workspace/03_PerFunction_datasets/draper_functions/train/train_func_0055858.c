__ecereNameSpace__ecere__com___mycrealloc(void * pointer, unsigned int size)
{
struct __ecereNameSpace__ecere__com__MemBlock * block = pointer ? ((struct __ecereNameSpace__ecere__com__MemBlock *)((unsigned char *)pointer - sizeof(struct __ecereNameSpace__ecere__com__MemBlock))) : (((void *)0));
void * newPointer = (((void *)0));
struct __ecereNameSpace__ecere__com__MemPart * part = block ? block->part : (((void *)0));
struct __ecereNameSpace__ecere__com__BlockPool * pool = part ? part->pool : (((void *)0));

if(block)
{
if(pool)
{
unsigned int ns = __ecereNameSpace__ecere__com__pow1_5i(size);
unsigned int mod = ns % 4;

if(mod)
ns += 4 - mod;
if(ns == (*pool).blockSize)
{
int extra = size - block->size;

newPointer = pointer;
(*pool).usedSpace += extra;
if(extra > 0)
memset((unsigned char *)pointer + block->size, (unsigned char)0, extra);
block->size = size;
}
}
else if(size)
{
struct __ecereNameSpace__ecere__com__MemBlock * newBlock = realloc(block, sizeof(struct __ecereNameSpace__ecere__com__MemBlock) + size);

if(newBlock)
{
int extra = size - newBlock->size;

__ecereNameSpace__ecere__com__TOTAL_MEM += extra;
__ecereNameSpace__ecere__com__OUTSIDE_MEM += extra;
newPointer = ((struct __ecereNameSpace__ecere__com__MemBlock *)newBlock + 1);
if(extra > 0)
memset((unsigned char *)newPointer + newBlock->size, (unsigned char)0, extra);
newBlock->size = size;
}
}
}
if(!newPointer)
{
newPointer = __ecereNameSpace__ecere__com___mymalloc(size);
if(newPointer)
{
if(pointer)
{
unsigned int __simpleStruct0;

memcpy(newPointer, pointer, (__simpleStruct0 = block->size, (size < __simpleStruct0) ? size : __simpleStruct0));
if(size > block->size)
memset((unsigned char *)newPointer + block->size, (unsigned char)0, size - block->size);
__ecereNameSpace__ecere__com___myfree(pointer);
}
else
memset((unsigned char *)newPointer, (unsigned char)0, size);
}
}
return newPointer;
}
