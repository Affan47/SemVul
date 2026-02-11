IsSpaceEquivalent(const int ch, const int style) {
        return isspace(ch)
                || style == SCE_T3_BLOCK_COMMENT
                || style == SCE_T3_LINE_COMMENT
                || style == SCE_T3_PREPROCESSOR;
}
