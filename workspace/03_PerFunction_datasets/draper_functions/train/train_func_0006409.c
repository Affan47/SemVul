write(const void *data, size_t nbytes)
{
    if (doindent && !notlinehead)
    {
        if (level)
        {
            reserve(level);
            for (size_t i=0; i<level; i++)
            {
                this->data[offset] = '\t';
                offset++;
            }
        }
        notlinehead = 1;
    }
    reserve(nbytes);
    memcpy(this->data + offset, data, nbytes);
    offset += nbytes;
}
