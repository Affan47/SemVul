cr_statement_at_import_rule_set_imported_sheet (CRStatement * a_this,
                                                CRStyleSheet * a_sheet)
{
        g_return_val_if_fail (a_this
                              && a_this->type == AT_IMPORT_RULE_STMT
                              && a_this->kind.import_rule,
                              CR_BAD_PARAM_ERROR);

        a_this->kind.import_rule->sheet = a_sheet;

        return CR_OK;
}
