appendShortStringElement(const char *src, int32_t len, char *result, int32_t *resultSize, int32_t capacity, char arg)
{
    if(len) {
        if(*resultSize) {
            if(*resultSize < capacity) {
                uprv_strcat(result, "_");
            }
            (*resultSize)++;
        }
        *resultSize += len + 1;
        if(*resultSize < capacity) {
            uprv_strncat(result, &arg, 1);
            uprv_strncat(result, src, len);
        }
    }
}
