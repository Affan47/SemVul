translate(UString::Rep*& location, const char *c, unsigned hash)
    {
        size_t length = strlen(c);
        UChar *d = static_cast<UChar *>(fastMalloc(sizeof(UChar) * length));
        for (size_t i = 0; i != length; i++)
            d[i] = c[i];

        UString::Rep *r = UString::Rep::create(d, static_cast<int>(length)).releaseRef();
        r->isIdentifier = 1;
        r->rc = 0;
        r->_hash = hash;

        location = r;
    }
}
