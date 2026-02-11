enlarge() const
{
    bufferallocsize_+= BUFFER_SIZE;

    char* temp = new char[bufferallocsize_];
    std::memcpy(temp, buffer_, buffersize_);
    delete [] buffer_;
    buffer_ = temp;
}
