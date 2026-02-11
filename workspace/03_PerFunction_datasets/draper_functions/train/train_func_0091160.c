inspect(char **s, int *sz) const
{
    char str[256],ch[8];
    if (this->imageData) {
        if (this->nChannels>1) {
            if (this->colorModel[0]=='R') {
                if (this->nChannels==4)
                    strcpy(ch,"s(RGBA)");
                else strcpy(ch,"s(RGB)");
            } else if (this->colorModel[0]=='Y') {
                strcpy(ch,"s(YUV)");
            }
        } else strcpy(ch,"");
        sprintf(str,"CamImage : %dx%d, %dch%s, %dbpp",
            this->width, this->height, this->nChannels, ch,
            (this->depth&CAM_DEPTH_MASK));
    } else {
        sprintf(str,"CamImage : Unallocated");
    }
    *sz=strlen(str);
    *s=new char[*sz+1];
    strcpy(*s,str);
}
