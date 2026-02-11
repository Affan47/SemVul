_cleanBuffer() const
    {
        if ( mBuffer.mVoidBuffer != 0 ) {
            switch ( mBufferType ) {
                case bt_string:
                    delete mBuffer.mStrBuffer;
                    break;
                case bt_wstring:
                    delete mBuffer.mWStrBuffer;
                    break;
                case bt_utf32string:
                    delete mBuffer.mUTF32StrBuffer;
                    break;
                case bt_none:
                default:


                    assert("This should never happen - mVoidBuffer should never contain something if we "
                        "don't know the type");
                    break;
            }
            mBuffer.mVoidBuffer = 0;
            mBufferSize = 0;
            mBufferType = bt_none;
        }
    }
