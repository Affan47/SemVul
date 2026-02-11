get_numeric_property_value(PropertyValue * Value) {
    U8_T Res = 0;

    if (Value->mAccessFunc != NULL) {
        if (Value->mAccessFunc(Value, 0, &Res) < 0) exception(errno);
    }
    else if (Value->mAddr != NULL) {
        size_t i;
        for (i = 0; i < Value->mSize; i++) {
            Res = (Res << 8) | Value->mAddr[Value->mBigEndian ? i : Value->mSize - i - 1];
        }
    }
    else {
        Res = Value->mValue;
    }
    return Res;
}
