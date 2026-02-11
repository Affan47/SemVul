cr_font_size_set_absolute_font_size (CRFontSize *a_this,
                                     enum CRNumType a_num_type,
                                     gdouble a_value)
{
        g_return_val_if_fail (a_this, CR_BAD_PARAM_ERROR) ;
        g_return_val_if_fail ((unsigned)a_num_type < NB_NUM_TYPE,
                              CR_BAD_PARAM_ERROR) ;

        a_this->type = ABSOLUTE_FONT_SIZE ;
        cr_num_set (&a_this->value.absolute,
                    a_value, a_num_type) ;
        return CR_OK ;
}
