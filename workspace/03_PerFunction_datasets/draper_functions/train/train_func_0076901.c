is_valid(double epsilon) const
    {
        return fabs(sx) > epsilon && fabs(sy) > epsilon;
    }
