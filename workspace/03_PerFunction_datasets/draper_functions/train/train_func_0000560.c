__ecereMethod___ecereNameSpace__ecere__sys__BufferedFile_Seek(struct __ecereNameSpace__ecere__com__Instance * this, int pos, int mode)
{
struct __ecereNameSpace__ecere__sys__BufferedFile * __ecerePointer___ecereNameSpace__ecere__sys__BufferedFile = (struct __ecereNameSpace__ecere__sys__BufferedFile *)(this ? (((char *)this) + 20) : 0);
unsigned int newPosition = __ecerePointer___ecereNameSpace__ecere__sys__BufferedFile->pos;

switch(mode)
{
case 0:
newPosition = pos;
break;
case 1:
newPosition += pos;
break;
case 2:
{
newPosition = __ecerePointer___ecereNameSpace__ecere__sys__BufferedFile->fileSize + pos;
break;
}
}
if(__ecerePointer___ecereNameSpace__ecere__sys__BufferedFile->pos != newPosition)
{
if(newPosition >= __ecerePointer___ecereNameSpace__ecere__sys__BufferedFile->pos - __ecerePointer___ecereNameSpace__ecere__sys__BufferedFile->bufferPos && newPosition < __ecerePointer___ecereNameSpace__ecere__sys__BufferedFile->pos + __ecerePointer___ecereNameSpace__ecere__sys__BufferedFile->bufferSize)
{
if(newPosition < __ecerePointer___ecereNameSpace__ecere__sys__BufferedFile->pos - __ecerePointer___ecereNameSpace__ecere__sys__BufferedFile->bufferPos + __ecerePointer___ecereNameSpace__ecere__sys__BufferedFile->bufferCount)
__ecerePointer___ecereNameSpace__ecere__sys__BufferedFile->bufferPos += newPosition - __ecerePointer___ecereNameSpace__ecere__sys__BufferedFile->pos;
else
{
unsigned int read = newPosition - __ecerePointer___ecereNameSpace__ecere__sys__BufferedFile->pos - __ecerePointer___ecereNameSpace__ecere__sys__BufferedFile->bufferCount;

if(read < __ecerePointer___ecereNameSpace__ecere__sys__BufferedFile->bufferCount * 2)
{
if(read > __ecerePointer___ecereNameSpace__ecere__sys__BufferedFile->bufferSize)
{
__ecerePointer___ecereNameSpace__ecere__sys__BufferedFile->bufferCount = 0;
__ecerePointer___ecereNameSpace__ecere__sys__BufferedFile->bufferPos = 0;
}
else
{
((unsigned int (*)(struct __ecereNameSpace__ecere__com__Instance *, int pos, int mode))__ecerePointer___ecereNameSpace__ecere__sys__BufferedFile->handle->_vTbl[__ecereVMethodID___ecereNameSpace__ecere__sys__File_Seek])(__ecerePointer___ecereNameSpace__ecere__sys__BufferedFile->handle, __ecerePointer___ecereNameSpace__ecere__sys__BufferedFile->pos - __ecerePointer___ecereNameSpace__ecere__sys__BufferedFile->bufferPos + __ecerePointer___ecereNameSpace__ecere__sys__BufferedFile->bufferCount, 0);
read = ((int (*)(struct __ecereNameSpace__ecere__com__Instance *, void *  buffer, unsigned int size, unsigned int count))__ecerePointer___ecereNameSpace__ecere__sys__BufferedFile->handle->_vTbl[__ecereVMethodID___ecereNameSpace__ecere__sys__File_Read])(__ecerePointer___ecereNameSpace__ecere__sys__BufferedFile->handle, __ecerePointer___ecereNameSpace__ecere__sys__BufferedFile->buffer + __ecerePointer___ecereNameSpace__ecere__sys__BufferedFile->bufferCount, 1, read);
__ecerePointer___ecereNameSpace__ecere__sys__BufferedFile->bufferPos += newPosition - __ecerePointer___ecereNameSpace__ecere__sys__BufferedFile->pos;
__ecerePointer___ecereNameSpace__ecere__sys__BufferedFile->bufferCount += read;
}
}
else
{
__ecerePointer___ecereNameSpace__ecere__sys__BufferedFile->bufferCount = 0;
__ecerePointer___ecereNameSpace__ecere__sys__BufferedFile->bufferPos = 0;
}
}
}
else
{
__ecerePointer___ecereNameSpace__ecere__sys__BufferedFile->bufferCount = 0;
__ecerePointer___ecereNameSpace__ecere__sys__BufferedFile->bufferPos = 0;
}
__ecerePointer___ecereNameSpace__ecere__sys__BufferedFile->eof = newPosition > __ecerePointer___ecereNameSpace__ecere__sys__BufferedFile->fileSize;
__ecerePointer___ecereNameSpace__ecere__sys__BufferedFile->pos = newPosition;
}
return 0x1;
}
