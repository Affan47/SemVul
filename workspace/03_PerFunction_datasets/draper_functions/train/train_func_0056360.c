writeImageData(FileType type,
    boost::shared_ptr<IOChannel> out, const GnashImage& image, int quality)
{

    const size_t width = image.width();
    const size_t height = image.height();

    quality = clamp<int>(quality, 0, 100);

    std::auto_ptr<Output> outChannel;

    switch (type) {
#ifdef USE_PNG
        case GNASH_FILETYPE_PNG:
            outChannel = createPngOutput(out, width, height, quality);
            break;
#endif
        case GNASH_FILETYPE_JPEG:
            outChannel = JpegOutput::create(out, width, height, quality);
            break;
        default:
            log_error(_("Requested to write image as unsupported filetype"));
            break;
    }

    switch (image.type()) {
        case TYPE_RGB:
            outChannel->writeImageRGB(image.begin());
            break;
        case TYPE_RGBA:
            outChannel->writeImageRGBA(image.begin());
            break;
        default:
            break;
    }

}
