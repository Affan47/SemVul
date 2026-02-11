deallocate(void* p)
    {
        if (p)
        {
            unsigned char* mem = (unsigned char*)p;
            mem = mem - mem[-1];
            delete [] mem;
        }
    }
