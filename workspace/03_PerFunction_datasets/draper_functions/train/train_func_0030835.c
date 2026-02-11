load(const RawDataContainer& data, Texture* result)
{
    int width, height, comp;


    unsigned char* image = stbi_load_from_memory(data.getDataPtr(),
                                                 data.getSize(),
                                                 &width, &height, &comp, 0);

    if (!image)
    {
        Logger::getSingletonPtr()->logEvent(
            "STBImageCodec::load - Invalid image data", Errors);

        return 0;
    }

    Texture::PixelFormat format;
    switch (comp)
    {
    case 4:
        format = Texture::PF_RGBA;
        break;
    case 3:
        format = Texture::PF_RGB;
        break;
    default:
        Logger::getSingletonPtr()->logEvent(
            "STBImageCodec::load - Invalid image format. "
            "Only RGB and RGBA images are supported", Errors);

        stbi_image_free(image);
        return 0;
    }

    result->loadFromMemory(image,
                           Size(static_cast<float>(width),
                                static_cast<float>(height)),
                           format);


    stbi_image_free(image);

    return result;
}
