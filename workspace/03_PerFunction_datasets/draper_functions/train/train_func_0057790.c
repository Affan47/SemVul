setText(const UnicodeString &text, UErrorCode &status)
{
    if (U_SUCCESS(status)) {
        if (text.length() == 0) {
            status = U_ILLEGAL_ARGUMENT_ERROR;
        }
        else {
            m_text_        = text;
            m_search_->text = m_text_.getBuffer();
            m_search_->textLength = m_text_.length();
        }
    }
}
