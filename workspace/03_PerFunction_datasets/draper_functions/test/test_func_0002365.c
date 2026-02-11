insert(unsigned char value)
{
    unsigned int insertionPoint;

    if (2 >= length_)
        insertionPoint = length_;
    else
        insertionPoint = 2;
    unsigned int start;

    if (length_ >= SIZE)
        start = SIZE - 1;
    else
    {
        start = length_;
        length_++;
    }
    for (unsigned int k = start; k > insertionPoint; k--)
        buffer_[k] = buffer_[k - 1];
    buffer_[insertionPoint] = value;
}
