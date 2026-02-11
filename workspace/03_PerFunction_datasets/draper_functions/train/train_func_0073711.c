_TIFFPrettyPrintField(TIFF* tif, FILE* fd, ttag_t tag,
                      uint32 value_count, void *raw_data)
{
        TIFFDirectory *td = &tif->tif_dir;

        switch (tag)
        {
                case TIFFTAG_INKSET:
                        fprintf(fd, "  Ink Set: ");
                        switch (*((uint16*)raw_data)) {
                                case INKSET_CMYK:
                                        fprintf(fd, "CMYK\n");
                                        break;
                                default:
                                        fprintf(fd, "%u (0x%x)\n",
                                                *((uint16*)raw_data),
                                                *((uint16*)raw_data));
                                        break;
                        }
                        return 1;
                case TIFFTAG_DOTRANGE:
                        fprintf(fd, "  Dot Range: %u-%u\n",
                                ((uint16*)raw_data)[0], ((uint16*)raw_data)[1]);
                        return 1;
                case TIFFTAG_WHITEPOINT:
                        fprintf(fd, "  White Point: %g-%g\n",
                                ((float *)raw_data)[0], ((float *)raw_data)[1]);                        return 1;
                case TIFFTAG_REFERENCEBLACKWHITE:
                {
                        uint16 i;

                        fprintf(fd, "  Reference Black/White:\n");
                        for (i = 0; i < td->td_samplesperpixel; i++)
                        fprintf(fd, "    %2d: %5g %5g\n", i,
                                ((float *)raw_data)[2*i+0],
                                ((float *)raw_data)[2*i+1]);
                        return 1;
                }
                case TIFFTAG_XMLPACKET:
                {
                        uint32 i;

                        fprintf(fd, "  XMLPacket (XMP Metadata):\n" );
                        for(i = 0; i < value_count; i++)
                                fputc(((char *)raw_data)[i], fd);
                        fprintf( fd, "\n" );
                        return 1;
                }
                case TIFFTAG_RICHTIFFIPTC:


                        fprintf(fd,
                                "  RichTIFFIPTC Data: <present>, %lu bytes\n",
                                (unsigned long) value_count * 4);
                        return 1;
                case TIFFTAG_PHOTOSHOP:
                        fprintf(fd, "  Photoshop Data: <present>, %lu bytes\n",
                                (unsigned long) value_count);
                        return 1;
                case TIFFTAG_ICCPROFILE:
                        fprintf(fd, "  ICC Profile: <present>, %lu bytes\n",
                                (unsigned long) value_count);
                        return 1;
                case TIFFTAG_STONITS:
                        fprintf(fd,
                                "  Sample to Nits conversion factor: %.4e\n",
                                *((double*)raw_data));
                        return 1;
        }

        return 0;
}
