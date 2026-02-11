GetClassValidator()
{
#if wxUSE_VALIDATORS
    WX_PG_DOGETVALIDATOR_ENTRY()

    wxValidator* validator = new wxNumericPropertyValidator(
                                    wxNumericPropertyValidator::Signed);

    WX_PG_DOGETVALIDATOR_EXIT(validator)
#else
    return NULL;
#endif
}
