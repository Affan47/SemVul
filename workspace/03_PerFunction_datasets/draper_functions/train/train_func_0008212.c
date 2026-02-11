__ecereMethod___ecereNameSpace__ecere__sys__BufferedFile_Write(struct __ecereNameSpace__ecere__com__Instance * this, unsigned char * buffer, unsigned int size, unsigned int count)
{
unsigned int __simpleStruct0, __simpleStruct1;
struct __ecereNameSpace__ecere__sys__BufferedFile * __ecerePointer___ecereNameSpace__ecere__sys__BufferedFile = (struct __ecereNameSpace__ecere__sys__BufferedFile *)(this ? (((char *)this) + 20) : 0);
unsigned int result;
unsigned int numBytes;
unsigned int bytesToBuffer;
unsigned int missing;

((unsigned int (*)(struct __ecereNameSpace__ecere__com__Instance *, int pos, int mode))__ecerePointer___ecereNameSpace__ecere__sys__BufferedFile->handle->_vTbl[__ecereVMethodID___ecereNameSpace__ecere__sys__File_Seek])(__ecerePointer___ecereNameSpace__ecere__sys__BufferedFile->handle, __ecerePointer___ecereNameSpace__ecere__sys__BufferedFile->pos, 0);
result = ((int (*)(struct __ecereNameSpace__ecere__com__Instance *, void *  buffer, unsigned int size, unsigned int count))__ecerePointer___ecereNameSpace__ecere__sys__BufferedFile->handle->_vTbl[__ecereVMethodID___ecereNameSpace__ecere__sys__File_Write])(__ecerePointer___ecereNameSpace__ecere__sys__BufferedFile->handle, buffer, size, count);
numBytes = result * size;
bytesToBuffer = (__ecerePointer___ecereNameSpace__ecere__sys__BufferedFile->bufferSize > __ecerePointer___ecereNameSpace__ecere__sys__BufferedFile->bufferPos) ? (__ecerePointer___ecereNameSpace__ecere__sys__BufferedFile->bufferSize - __ecerePointer___ecereNameSpace__ecere__sys__BufferedFile->bufferPos) : 0;
missing = numBytes - bytesToBuffer;
__ecerePointer___ecereNameSpace__ecere__sys__BufferedFile->pos += numBytes;
__ecerePointer___ecereNameSpace__ecere__sys__BufferedFile->fileSize = (__simpleStruct0 = __ecerePointer___ecereNameSpace__ecere__sys__BufferedFile->fileSize, __simpleStruct1 = __ecerePointer___ecereNameSpace__ecere__sys__BufferedFile->pos, (__simpleStruct0 > __simpleStruct1) ? __simpleStruct0 : __simpleStruct1);
if(bytesToBuffer < numBytes && __ecerePointer___ecereNameSpace__ecere__sys__BufferedFile->bufferCount >= __ecerePointer___ecereNameSpace__ecere__sys__BufferedFile->bufferPos && numBytes < __ecerePointer___ecereNameSpace__ecere__sys__BufferedFile->bufferSize && missing < __ecerePointer___ecereNameSpace__ecere__sys__BufferedFile->bufferPos)
{
memcpy(__ecerePointer___ecereNameSpace__ecere__sys__BufferedFile->buffer, __ecerePointer___ecereNameSpace__ecere__sys__BufferedFile->buffer + missing, __ecerePointer___ecereNameSpace__ecere__sys__BufferedFile->bufferPos - missing);
__ecerePointer___ecereNameSpace__ecere__sys__BufferedFile->bufferPos -= missing;
__ecerePointer___ecereNameSpace__ecere__sys__BufferedFile->bufferCount -= missing;
bytesToBuffer += missing;
}
if(bytesToBuffer >= numBytes)
{
unsigned int __simpleStruct0, __simpleStruct1;

bytesToBuffer = numBytes;
memcpy(__ecerePointer___ecereNameSpace__ecere__sys__BufferedFile->buffer + __ecerePointer___ecereNameSpace__ecere__sys__BufferedFile->bufferPos, buffer, bytesToBuffer);
__ecerePointer___ecereNameSpace__ecere__sys__BufferedFile->bufferPos += bytesToBuffer;
__ecerePointer___ecereNameSpace__ecere__sys__BufferedFile->bufferCount = (__simpleStruct0 = __ecerePointer___ecereNameSpace__ecere__sys__BufferedFile->bufferCount, __simpleStruct1 = __ecerePointer___ecereNameSpace__ecere__sys__BufferedFile->bufferPos, (__simpleStruct0 > __simpleStruct1) ? __simpleStruct0 : __simpleStruct1);
}
else
{
unsigned int __simpleStruct0;

bytesToBuffer = (__simpleStruct0 = __ecerePointer___ecereNameSpace__ecere__sys__BufferedFile->bufferSize, (numBytes < __simpleStruct0) ? numBytes : __simpleStruct0);
memcpy(__ecerePointer___ecereNameSpace__ecere__sys__BufferedFile->buffer, buffer + numBytes - bytesToBuffer, bytesToBuffer);
__ecerePointer___ecereNameSpace__ecere__sys__BufferedFile->bufferPos = bytesToBuffer;
__ecerePointer___ecereNameSpace__ecere__sys__BufferedFile->bufferCount = bytesToBuffer;
}
return result;
}
