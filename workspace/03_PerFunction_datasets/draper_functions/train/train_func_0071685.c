gl_label_barcode_style_is_equal (const glLabelBarcodeStyle *style1,
                                 const glLabelBarcodeStyle *style2)
{


        if ( style1 == NULL )
        {
                return ( style2 == NULL );
        }
        else
        {
                if ( style2 == NULL )
                {
                        return FALSE;
                }
        }


        if ( style1->text_flag != style2->text_flag )
        {
                return FALSE;
        }
        if ( style1->checksum_flag != style2->checksum_flag )
        {
                return FALSE;
        }
        if ( style1->format_digits != style2->format_digits )
        {
                return FALSE;
        }
        if ( style1->backend_id && style2->backend_id )
        {
                if ( strcmp (style1->backend_id, style2->backend_id) != 0 )
                {
                        return FALSE;
                }
        }
        else
        {
                if ( style1->backend_id != style2->backend_id )
                {
                        return FALSE;
                }
        }
        if ( style1->id && style2->id )
        {
                if ( strcmp (style1->id, style2->id) != 0 )
                {
                        return FALSE;
                }
        }
        else
        {
                if ( style1->id != style2->id )
                {
                        return FALSE;
                }
        }


        return TRUE;
}
