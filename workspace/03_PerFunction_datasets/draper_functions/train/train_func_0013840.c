lgl_barcode_free (lglBarcode *bc)
{
        GList *p;

        if (bc != NULL)
        {

                for (p = bc->shapes; p != NULL; p = p->next)
                {
                        lgl_barcode_shape_free ((lglBarcodeShape *)p->data);
                }
                g_list_free (bc->shapes);

                g_free (bc);

        }
}
