dxf_thumbnail_read
(
        DxfFile *fp,

        DxfThumbnail *dxf_thumbnail

)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        char *temp_string = NULL;
        int i;
        int preview_data_length = 0;


        if (dxf_thumbnail == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                dxf_thumbnail = dxf_thumbnail_new ();
                dxf_thumbnail = dxf_thumbnail_init (dxf_thumbnail);
        }
        if (fp->acad_version_number < AutoCAD_2000)
        {
                fprintf (stderr,
                  (_("Warning in %s () illegal DXF version for this entity.\n")),
                  __FUNCTION__);
        }
        i = 0;
        (fp->line_number)++;
        fscanf (fp->fp, "%[^\n]", temp_string);
        while (strcmp (temp_string, "0") != 0)
        {
                if (ferror (fp->fp))
                {
                        fprintf (stderr,
                          (_("Error in %s () while reading from: %s in line: %d.\n")),
                          __FUNCTION__, fp->filename, fp->line_number);
                        fclose (fp->fp);
                        return (NULL);
                }
                else if (strcmp (temp_string, "90") == 0)
                {


                        (fp->line_number)++;
                        fscanf (fp->fp, "%d\n", &dxf_thumbnail->number_of_bytes);
                }
                else if (strcmp (temp_string, "310") == 0)
                {


                        (fp->line_number)++;
                        fscanf (fp->fp, "%s\n", dxf_thumbnail->preview_image_data[i]);
                        preview_data_length = preview_data_length + strlen (dxf_thumbnail->preview_image_data[i]);
                        i++;
                }
                else if (strcmp (temp_string, "999") == 0)
                {

                        (fp->line_number)++;
                        fscanf (fp->fp, "%s\n", temp_string);
                        fprintf (stdout, "DXF comment: %s\n", temp_string);
                }
                else
                {
                        fprintf (stderr,
                          (_("Warning in %s () unknown string tag found while reading from: %s in line: %d.\n")),
                          __FUNCTION__, fp->filename, fp->line_number);
                }
        }

        if (preview_data_length != dxf_thumbnail->number_of_bytes)
        {
                        fprintf (stderr,
                          (_("Warning in %s () read %d preview data bytes from %s while %d were expected.\n")),
                          __FUNCTION__, preview_data_length,
                          fp->filename, dxf_thumbnail->number_of_bytes);
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (dxf_thumbnail);
}
