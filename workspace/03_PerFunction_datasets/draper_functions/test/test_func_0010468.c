destroy()
{
    if (this->own_memory)
    {
	delete [] this->buf;
    }
    this->size = 0;
    this->buf = 0;
}
