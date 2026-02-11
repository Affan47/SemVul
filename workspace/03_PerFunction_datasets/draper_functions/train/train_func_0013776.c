isHardwareFilteringSupported(TextureType ttype, PixelFormat format, int usage,
            bool preciseFormatOnly)
    {
        if (format == PF_UNKNOWN)
            return false;


        PixelFormat nativeFormat = getNativeFormat(ttype, format, usage);
        if (preciseFormatOnly && format != nativeFormat)
            return false;


        if (!PixelUtil::isFloatingPoint(nativeFormat))
            return true;


        static const String sFloat16SupportedCards[] =
        {

            "*GeForce*8800*",


            "*GeForce*7950*",
            "*GeForce*7900*",
            "*GeForce*7800*",
            "*GeForce*7600*",
            "*GeForce*7500*",
            "*GeForce*7300*",


            "*GeForce*6800*",
            "*GeForce*6700*",
            "*GeForce*6600*",
            "*GeForce*6500*",

            ""
        };


        static const String sFloat32SupportedCards[] =
        {

            "*GeForce*8800*",

            ""
        };

        PixelComponentType pct = PixelUtil::getComponentType(nativeFormat);
        const String* supportedCards;
        switch (pct)
        {
        case PCT_FLOAT16:
            supportedCards = sFloat16SupportedCards;
            break;
        case PCT_FLOAT32:
            supportedCards = sFloat32SupportedCards;
            break;
        default:
            return false;
        }

        const GLubyte* pcRenderer = glGetString(GL_RENDERER);
        String str = (const char*)pcRenderer;

        for (; !supportedCards->empty(); ++supportedCards)
        {
            if (StringUtil::match(str, *supportedCards))
            {
                return true;
            }
        }

        return false;
    }
