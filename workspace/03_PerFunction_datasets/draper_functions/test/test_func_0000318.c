evaluate(double* res, int length, Renderer*) const
    {
        if (res && length < 1)
            return -1;
        if (res)
            *res = value;
        return 1;
    }
