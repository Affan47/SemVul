rfind( unicode_char ch, size_type index  ) const
    {
        code_point cp[3] = {0, 0, 0};
        size_t l = _utf32_to_utf16( ch, cp );
        return rfind( UTFString( cp, l ), index );
    }
