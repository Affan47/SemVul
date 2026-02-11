push(unsigned char data)
    {
        if(this->_size>=this->total_words)
            return(NULL);

        this->data[this->_size]=data;
        this->_size++;
        return(&(this->data[this->_size-1]));
    }
