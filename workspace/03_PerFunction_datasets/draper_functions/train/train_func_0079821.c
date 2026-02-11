GenLayer(FileDesc,Technology,Mask)

FILE *FileDesc;
char Technology,Mask[];
{
    if (Technology > ' ') {
        fprintf(FileDesc,"L %c",Technology);
        if (Mask[0] > ' ') {
            fprintf(FileDesc,"%c",Mask[0]);
            if (Mask[1] > ' ') {
                fprintf(FileDesc,"%c",Mask[1]);
                if (Mask[2] > ' ')
                    fprintf(FileDesc,"%c",Mask[2]);
            }
        }
        fprintf(FileDesc,";\n");
    }
}
