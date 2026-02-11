dxf_ltype_free
(
        DxfLType *dxf_ltype


)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        int i;

        if (dxf_ltype->next != NULL)
        {
              fprintf (stderr,
                (_("Error in %s () pointer to next DxfLType was not NULL.\n")),
                __FUNCTION__);
              return (EXIT_FAILURE);
        }
        free (dxf_ltype->linetype_name);
        free (dxf_ltype->description);
        for ((i = 0); (i <= dxf_ltype->number_of_linetype_elements); i++)
        {
                dxf_ltype->complex_text_string[i] = NULL;
                dxf_ltype->complex_style_pointer[i] = NULL;
        }
        free (dxf_ltype->dictionary_owner_soft);
        free (dxf_ltype->dictionary_owner_hard);
        free (dxf_ltype);
        dxf_ltype = NULL;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (EXIT_SUCCESS);
}
