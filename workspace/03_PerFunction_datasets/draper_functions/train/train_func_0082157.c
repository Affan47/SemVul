write(unsigned char* buf, size_t len)
{
    Buffer* b = new Buffer(len);
    memcpy(b->getBuffer(), buf, len);
    this->data.push_back(b);
    this->ready = false;
    this->total_size += len;

    if (getNext(true))
    {
	getNext()->write(buf, len);
    }
}
