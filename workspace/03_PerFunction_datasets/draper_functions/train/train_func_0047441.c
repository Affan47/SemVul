lookup(unsigned char value, unsigned int &index)
{
    for (unsigned int i = 0; i < length_; i++)
        if (value == buffer_[i])
        {
            index = i;
            if (i)
            {
                unsigned int target = (i >> 1);

                do
                {
                    buffer_[i] = buffer_[i - 1];
                    i--;
                }
                while (i > target);
                buffer_[target] = value;
            }
            return 1;
        }
    insert(value);
    return 0;
}
