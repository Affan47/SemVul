appendTag(
    const char* tag,
    int32_t tagLength,
    char* buffer,
    int32_t* bufferLength) {

    if (*bufferLength > 0) {
        buffer[*bufferLength] = '_';
        ++(*bufferLength);
    }

    uprv_memmove(
        &buffer[*bufferLength],
        tag,
        tagLength);

    *bufferLength += tagLength;
}
