read(Matrix4* m, size_t count)
    {
        for (size_t i = 0; i < count; ++i, ++m)
        {
            read((*m)[0], 12);
        }
    }
