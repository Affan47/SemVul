readDataIntoBuffer(int maxSize)
{
    if (maxSize > MaxBufferSize)
        return 0;

    int numBytesBeforeRead = buffer.size();
    if (numBytesBeforeRead == MaxBufferSize) {
        abort();
        return 0;
    }

    while (bytesAvailable() > 0 && buffer.size() < maxSize) {
        buffer.append(read(1));
        if (buffer.endsWith(SeparatorToken))
            break;
    }
    return buffer.size() - numBytesBeforeRead;
}
