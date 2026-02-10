possibleBufferOverrunError(const Token *tok, const std::string &src, const std::string &dst, bool cat)
{
    if (cat)
        reportError(tok, Severity::warning, "possibleBufferAccessOutOfBounds",
                    "Possible buffer overflow if strlen(" + src + ") is larger than sizeof(" + dst + ")-strlen(" + dst +").\n"
                    "Possible buffer overflow if strlen(" + src + ") is larger than sizeof(" + dst + ")-strlen(" + dst +"). "
                    "The source buffer is larger than the destination buffer so there is the potential for overflowing the destination buffer.");
    else
        reportError(tok, Severity::warning, "possibleBufferAccessOutOfBounds",
                    "Possible buffer overflow if strlen(" + src + ") is larger than or equal to sizeof(" + dst + ").\n"
                    "Possible buffer overflow if strlen(" + src + ") is larger than or equal to sizeof(" + dst + "). "
                    "The source buffer is larger than the destination buffer so there is the potential for overflowing the destination buffer.");
}
