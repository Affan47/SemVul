print_jp2c_compression(struct image_summary *entry)
{
    char *transform;
    char *quantization;
    int chpr = 0;

    transform = quantization = NULLSTRING;
    if(entry)
    {
        if((entry->compression & 0xff) == 1)
            transform = "5/3 reversible";
        else
            transform = "9/7 irreversible";
        switch((entry->compression & 0xff00) >> 8)
        {
            case 0:
                quantization = "no quantization";
                break;
            case 1:
                quantization = "implicit quantization";
                break;
            case 2:
                quantization = "explicit quantization";
                break;
            default:
                quantization = "unknown quantization";
                break;
        }
    }
    chpr += printf(" (%s compression with %s)",transform,quantization);
    setcharsprinted(chpr);
}
