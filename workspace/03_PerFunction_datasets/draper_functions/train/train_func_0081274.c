makeArrayIndexOutOfBoundsError(std::ostream& oss, const CheckBufferOverrun::ArrayInfo &arrayInfo, const std::vector<MathLib::bigint> &index)
{
    oss << "Array '" << arrayInfo.varname();
    for (unsigned int i = 0; i < arrayInfo.num().size(); ++i)
        oss << "[" << arrayInfo.num(i) << "]";
    if (index.size() == 1)
        oss << "' accessed at index " << index[0] << ", which is";
    else {
        oss << "' index " << arrayInfo.varname();
        for (unsigned int i = 0; i < index.size(); ++i)
            oss << "[" << index[i] << "]";
    }
    oss << " out of bounds.";
}
