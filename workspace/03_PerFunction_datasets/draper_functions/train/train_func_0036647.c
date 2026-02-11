add_r24(const char* image_file,
            const char *fname,
            int32 file_id,
            intn il,
            int32 vgroup_id)
{
    int32  ri_ref;
    char   *srcdir = getenv("srcdir");
    char   data_file[512]="";


    if ( srcdir )
    {
        strcpy(data_file, srcdir);
        strcat(data_file, "/");
    }
    strcat( data_file, image_file);

    if ( read_data(data_file) > 0 )
    {

        if (DF24setil(il)==FAIL){
            printf( "Could not set interlace for image\n");
            return FAIL;
        }


        if (DF24addimage(fname, g_image_data, g_lenght_x, g_lenght_y)==FAIL){
            printf( "Could not write image\n");
            return FAIL;
        }


        ri_ref = DF24lastref();


        if (vgroup_id)
        {
            if (Vaddtagref (vgroup_id, TAG_GRP_IMAGE, ri_ref)==FAIL)
            {
                printf( "Could not set group for image\n");
                return FAIL;
            }
        }


        if (add_an(file_id, TAG_GRP_IMAGE, ri_ref)<0)
            return FAIL;

    }

    if ( g_image_data != NULL )
    {
        free( g_image_data );
        g_image_data=NULL;
    }

    return SUCCEED;
}
