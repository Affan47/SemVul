dxf_class_write
(
        DxfFile *fp,

        DxfClass *dxf_class

)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        char *dxf_entity_name = strdup ("CLASS");


        if (dxf_class == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (!dxf_class->record_type
                || (strcmp (dxf_class->record_type, "") == 0))
        {
                fprintf (stderr,
                  (_("Error in %s () empty record type string for the %s entity\n")),
                  __FUNCTION__, dxf_entity_name);
                return (EXIT_FAILURE);
        }
        if (!dxf_class->record_name)
        {
                fprintf (stderr,
                  (_("Warning in %s () empty record name string for the %s entity\n")),
                  __FUNCTION__, dxf_entity_name);
                fprintf (stderr,
                  (_("\trecord_name of %s entity is reset to \"\"")),
                  dxf_entity_name );
                dxf_class->record_name = strdup ("");
        }
        if (!dxf_class->class_name
                || (strcmp (dxf_class->class_name, "") == 0))
        {
                fprintf (stderr,
                  (_("Error in %s () empty class name string for the %s entity\n")),
                  __FUNCTION__, dxf_entity_name);
                return (EXIT_FAILURE);
        }
        if (!dxf_class->app_name)
        {
                fprintf (stderr,
                  (_("Warning in %s () empty app name string for the %s entity\n")),
                  __FUNCTION__, dxf_entity_name);
                fprintf (stderr,
                  (_("\tapp_name of %s entity is reset to \"\"")),
                  dxf_entity_name );
                dxf_class->app_name = strdup ("");
        }

        fprintf (fp->fp, "  0\n%s\n", dxf_entity_name);
        fprintf (fp->fp, "  1\n%s\n", dxf_class->record_name);
        fprintf (fp->fp, "  2\n%s\n", dxf_class->class_name);
        if (fp->acad_version_number >= AutoCAD_14)
        {
                fprintf (fp->fp, "  3\n%s\n", dxf_class->app_name);
        }
        fprintf (fp->fp, " 90\n%d\n", dxf_class->proxy_cap_flag);
        fprintf (fp->fp, "280\n%d\n", dxf_class->was_a_proxy_flag);
        fprintf (fp->fp, "281\n%d\n", dxf_class->is_an_entity_flag);
#if DEBUG
        DXF_DEBUG_END
#endif
        return (EXIT_SUCCESS);
}
