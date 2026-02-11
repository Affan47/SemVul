operator=(string_set const &other)
        {
            if(this!=&other) {
                string_set tmp(other);
                swap(tmp);
            }
            return *this;
        }
