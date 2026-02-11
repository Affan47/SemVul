getSide (const AxisAlignedBox& box) const
    {
        if (box.isNull())
            return NO_SIDE;
        if (box.isInfinite())
            return BOTH_SIDE;

        return getSide(box.getCenter(), box.getHalfSize());
    }
