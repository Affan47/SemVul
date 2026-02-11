gl_format_and_type_to_mesa_format(GLenum format, GLenum type)
{
    switch (format)
    {
        case GL_RGB:
            switch (type) {
                case GL_UNSIGNED_SHORT_5_6_5:
                    return MESA_FORMAT_B5G6R5_UNORM;
                case GL_UNSIGNED_SHORT_5_6_5_REV:
                    return MESA_FORMAT_R5G6B5_UNORM;
            }
            break;
        case GL_RGBA:
            switch (type) {
                case GL_FLOAT:
                    return MESA_FORMAT_RGBA_FLOAT32;
                case GL_UNSIGNED_SHORT_5_5_5_1:
                    return MESA_FORMAT_A1B5G5R5_UNORM;
                case GL_UNSIGNED_INT_8_8_8_8:
                    return MESA_FORMAT_A8B8G8R8_UNORM;
                case GL_UNSIGNED_BYTE:
                case GL_UNSIGNED_INT_8_8_8_8_REV:
                    return MESA_FORMAT_R8G8B8A8_UNORM;
            }
            break;
        case GL_BGRA:
            switch (type) {
                case GL_UNSIGNED_SHORT_4_4_4_4:
                    return MESA_FORMAT_A4R4G4B4_UNORM;
                case GL_UNSIGNED_SHORT_4_4_4_4_REV:
                    return MESA_FORMAT_B4G4R4A4_UNORM;
                case GL_UNSIGNED_SHORT_5_5_5_1:
                    return MESA_FORMAT_A1R5G5B5_UNORM;
                case GL_UNSIGNED_SHORT_1_5_5_5_REV:
                    return MESA_FORMAT_B5G5R5A1_UNORM;
                case GL_UNSIGNED_INT_8_8_8_8:
                    return MESA_FORMAT_A8R8G8B8_UNORM;
                case GL_UNSIGNED_BYTE:
                case GL_UNSIGNED_INT_8_8_8_8_REV:
                    return MESA_FORMAT_B8G8R8A8_UNORM;

            }
            break;
    }

    return MESA_FORMAT_NONE;
}
