__ecereMethod___ecereNameSpace__ecere__com__SerialBuffer_WriteData(struct __ecereNameSpace__ecere__com__Instance * this, unsigned char * bytes, unsigned int numBytes)
{
struct __ecereNameSpace__ecere__com__SerialBuffer * __ecerePointer___ecereNameSpace__ecere__com__SerialBuffer = (struct __ecereNameSpace__ecere__com__SerialBuffer *)(this ? (((char *)this) + __ecereClass___ecereNameSpace__ecere__com__SerialBuffer->offset) : 0);

if(this != (((void *)0)))
{
if(__ecerePointer___ecereNameSpace__ecere__com__SerialBuffer->count + numBytes > __ecerePointer___ecereNameSpace__ecere__com__SerialBuffer->_size)
{
__ecerePointer___ecereNameSpace__ecere__com__SerialBuffer->_size = __ecerePointer___ecereNameSpace__ecere__com__SerialBuffer->count + numBytes;
__ecerePointer___ecereNameSpace__ecere__com__SerialBuffer->_size += __ecerePointer___ecereNameSpace__ecere__com__SerialBuffer->_size / 2;
__ecerePointer___ecereNameSpace__ecere__com__SerialBuffer->_buffer = __ecereNameSpace__ecere__com__eSystem_Renew(__ecerePointer___ecereNameSpace__ecere__com__SerialBuffer->_buffer, sizeof(unsigned char) * (__ecerePointer___ecereNameSpace__ecere__com__SerialBuffer->_size));
}
memcpy(__ecerePointer___ecereNameSpace__ecere__com__SerialBuffer->_buffer + __ecerePointer___ecereNameSpace__ecere__com__SerialBuffer->count, bytes, numBytes);
__ecerePointer___ecereNameSpace__ecere__com__SerialBuffer->count += numBytes;
return numBytes;
}
return 0;
}
