ToString(void) const
{
    std::ostringstream oss;

    oss << "Vector" << mDimensions << " (";

    for (int i=0; i<mDimensions; i++) {
        oss << mPoints->at(i);

        if (i < mDimensions-1)
            oss << ", ";
    }

    oss << ")";

    return oss.str();
}
