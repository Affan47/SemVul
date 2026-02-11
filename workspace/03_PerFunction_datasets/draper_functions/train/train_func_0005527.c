attributesWithOverride(PropertyDescriptor& other) const
{
    unsigned int mismatch = other.m_attributes ^ m_attributes;
    unsigned int sharedSeen = other.m_setAttributes & m_setAttributes;
    unsigned int newAttributes = m_attributes & (DontEnum|DontDelete|ReadOnly);

    if ((sharedSeen & WritableSet) && (mismatch & ReadOnly))
        newAttributes ^= ReadOnly;
    if ((sharedSeen & ConfigurableSet) && (mismatch & DontDelete))
        newAttributes ^= DontDelete;
    if ((sharedSeen & EnumerableSet) && (mismatch & DontEnum))
        newAttributes ^= DontEnum;

    return newAttributes;
}
