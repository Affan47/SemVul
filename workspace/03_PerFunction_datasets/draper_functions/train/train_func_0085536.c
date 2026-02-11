__ecereProp___ecereNameSpace__ecere__com__SerialBuffer_Get_size(struct __ecereNameSpace__ecere__com__Instance * this)
{
struct __ecereNameSpace__ecere__com__SerialBuffer * __ecerePointer___ecereNameSpace__ecere__com__SerialBuffer = (struct __ecereNameSpace__ecere__com__SerialBuffer *)(this ? (((char *)this) + __ecereClass___ecereNameSpace__ecere__com__SerialBuffer->offset) : 0);

return __ecerePointer___ecereNameSpace__ecere__com__SerialBuffer->count - __ecerePointer___ecereNameSpace__ecere__com__SerialBuffer->pos;
}
