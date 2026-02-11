swap_col(int i,int j)
    {
        size_t sz=sizeof(Nomial *)*this->rows;

        Nomial **tmp=new Nomial *[this->rows];

        memcpy(tmp,this->nomial+i*this->rows,sz);
        memcpy(this->nomial+i*this->rows,
               this->nomial+j*this->rows,sz);
        memcpy(this->nomial+j*this->rows,tmp,sz);

        delete tmp;
    }
