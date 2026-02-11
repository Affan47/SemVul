cr_token_set_important_sym (CRToken * a_this)
{
        g_return_val_if_fail (a_this, CR_BAD_PARAM_ERROR);
        cr_token_clear (a_this);
        a_this->type = IMPORTANT_SYM_TK;
        return CR_OK;
}
