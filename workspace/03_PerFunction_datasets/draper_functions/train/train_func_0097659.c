writePPM(FILE *stream,
                         const int bits,
                         const unsigned long frame)
{
    if ((stream != NULL) && (Image != NULL))
        return Image->writePPM(stream, frame, Image->getBits(bits));
    return 0;
}
