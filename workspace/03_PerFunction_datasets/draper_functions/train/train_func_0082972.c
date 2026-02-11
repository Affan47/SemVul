PrintBuffer()
{
    int i;
     for (i = 0; i < cSIZE; i++) {
        fprintf(stderr, "%02x ",(unsigned char)szSerBuffer[i]);
    }
    fprintf(stderr, "\n");
}
