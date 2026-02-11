operator==(const StackRule& o) const
{
    if (this == &o) return true;
    if (mParamCount != o.mParamCount) return false;
    return std::memcmp((const void*)(this + 2), (const void*)(&o + 2),
                       sizeof(StackType)*(mParamCount)) == 0;
}
