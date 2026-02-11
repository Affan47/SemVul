getCharClass(LEUnicode ch) const
{

    if (ch == C_SIGN_ZWJ) {
        return CC_ZERO_WIDTH_J_MARK;
    }

    if (ch == C_SIGN_ZWNJ) {
        return CC_ZERO_WIDTH_NJ_MARK;
    }

    if (ch < firstChar || ch > lastChar) {
        return CC_RESERVED;
    }

    return classTable[ch - firstChar];
}
