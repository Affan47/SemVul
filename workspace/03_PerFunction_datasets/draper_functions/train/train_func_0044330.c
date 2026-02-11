GetNumPackets(int data_size, int max_size)
    {
        int res1 = data_size % max_size;
        int res2 = data_size / max_size;
        return (res1) ? res2 + 1 : res2;
    }
