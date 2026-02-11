GetStr()
{
    TIXMLASSERT( _start );
    TIXMLASSERT( _end );
    if ( _flags & NEEDS_FLUSH ) {
        *_end = 0;
        _flags ^= NEEDS_FLUSH;

        if ( _flags ) {
            char* p = _start;
            char* q = _start;

            while( p < _end ) {
                if ( (_flags & NEEDS_NEWLINE_NORMALIZATION) && *p == CR ) {


                    if ( *(p+1) == LF ) {
                        p += 2;
                    }
                    else {
                        ++p;
                    }
                    *q++ = LF;
                }
                else if ( (_flags & NEEDS_NEWLINE_NORMALIZATION) && *p == LF ) {
                    if ( *(p+1) == CR ) {
                        p += 2;
                    }
                    else {
                        ++p;
                    }
                    *q++ = LF;
                }
                else if ( (_flags & NEEDS_ENTITY_PROCESSING) && *p == '&' ) {


                    if ( *(p+1) == '#' ) {
                        const int buflen = 10;
                        char buf[buflen] = { 0 };
                        int len = 0;
                        char* adjusted = const_cast<char*>( XMLUtil::GetCharacterRef( p, buf, &len ) );
                        if ( adjusted == 0 ) {
                            *q = *p;
                            ++p;
                            ++q;
                        }
                        else {
                            TIXMLASSERT( 0 <= len && len <= buflen );
                            TIXMLASSERT( q + len <= adjusted );
                            p = adjusted;
                            memcpy( q, buf, len );
                            q += len;
                        }
                    }
                    else {
                        int i=0;
                        for(; i<NUM_ENTITIES; ++i ) {
                            const Entity& entity = entities[i];
                            if ( strncmp( p + 1, entity.pattern, entity.length ) == 0
                                    && *( p + entity.length + 1 ) == ';' ) {

                                *q = entity.value;
                                ++q;
                                p += entity.length + 2;
                                break;
                            }
                        }
                        if ( i == NUM_ENTITIES ) {

                            ++p;
                            ++q;
                        }
                    }
                }
                else {
                    *q = *p;
                    ++p;
                    ++q;
                }
            }
            *q = 0;
        }


        if ( _flags & COLLAPSE_WHITESPACE ) {
            CollapseWhitespace();
        }
        _flags = (_flags & NEEDS_DELETE);
    }
    TIXMLASSERT( _start );
    return _start;
}
