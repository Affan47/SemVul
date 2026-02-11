pdf_put_composite(const gx_device_pdf * pdev, const byte * vstr, uint size, gs_id object_id)
{
    if (!pdev->KeyLength || object_id == (gs_id)-1) {
        if (pdev->ForOPDFRead && pdev->ProduceDSC) {
            stream_putc(pdev->strm, (byte)'\n');
            if (size > 255) {
                const byte *start, *p, *end, *save;
                int width = 0;

                end = vstr + size;
                start = p = vstr;
                while (p < end) {
                    if(*p == '\r' || *p == '\n') {
                        width = 0;
                        p++;
                        continue;
                    }
                    if (width > 254) {
                        save = p;

                        while (p > start) {
                            if (*p == '/' || *p == '[' || *p == '{' || *p == '(' || *p == ' ') {
                                stream_write(pdev->strm, start, p - start);
                                stream_putc(pdev->strm, (byte)'\n');
                                start = p;
                            }
                            else p--;
                        }
                        if (p == start) {
                            stream_write(pdev->strm, start, save - start);
                            stream_putc(pdev->strm, (byte)'\n');
                            start = save;
                        }
                    } else {
                        width++;
                        p++;
                    }
                }
            } else {
                stream_write(pdev->strm, vstr, size);
            }
        } else {
            stream_write(pdev->strm, vstr, size);
        }
    } else {
        const byte *p = vstr;
        int l = size, n;

        for (;l > 0 ;) {
            if (*p == '(')
                n = pdf_encrypt_encoded_string(pdev, p, l, object_id);
            else {
                n = pdf_scan_item(pdev, p, l, object_id);
                stream_write(pdev->strm, p, n);
            }
            l -= n;
            p += n;
        }
    }
    return 0;
}
