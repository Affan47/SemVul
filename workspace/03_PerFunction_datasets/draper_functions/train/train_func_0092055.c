allocateBuffer()
{
    if(mBuffer.data)

        return;
    mBuffer.data = new uint8[mSizeInBytes];

}
