array() const {
    beforeRead();
    verifyType(ARRAY);
    debugAssert(m_data != NULL);
    return *(m_data->value.a);
}
