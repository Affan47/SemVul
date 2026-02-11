blurVertical(QImage &image, unsigned int *stack, int div, int radius)
{
    int stackindex;
    int stackstart;

    quint32 * const pixels = reinterpret_cast<quint32 *>(image.bits());
    quint32 pixel;

    int w = image.width();
    int h = image.height();
    int hm = h - 1;

    int mul_sum = stack_blur8_mul[radius];
    int shr_sum = stack_blur8_shr[radius];

    unsigned int sum, sum_in, sum_out;

    for (int x = 0; x < w; x++)
    {
        sum     = 0;
        sum_in  = 0;
        sum_out = 0;

        pixel = pixels[x];
        for (int i = 0; i <= radius; i++)
        {
            stack[i] = qAlpha(pixel);

            sum += stack[i] * (i + 1);
            sum_out += stack[i];
        }

        for (int i = 1; i <= radius; i++)
        {
            pixel = pixels[qMin(i, hm) * w + x];

            unsigned int *stackpix = &stack[i + radius];
            *stackpix = qAlpha(pixel);

            sum    += *stackpix * (radius + 1 - i);
            sum_in += *stackpix;
        }

        stackindex = radius;
        for (int y = 0, i = x; y < h; y++, i += w)
        {
            pixels[i] = (((sum * mul_sum) >> shr_sum) << 24) & 0xff000000;

            sum -= sum_out;

            stackstart = stackindex + div - radius;
            if (stackstart >= div)
                stackstart -= div;

            unsigned int *stackpix = &stack[stackstart];

            sum_out -= *stackpix;

            pixel = pixels[qMin(y + radius + 1, hm) * w + x];

            *stackpix = qAlpha(pixel);

            sum_in += *stackpix;
            sum    += sum_in;

            if (++stackindex >= div)
                stackindex = 0;

            stackpix = &stack[stackindex];

            sum_out += *stackpix;
            sum_in  -= *stackpix;
        }
    }
}
