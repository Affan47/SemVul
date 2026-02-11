FcConfigLexBinding (FcConfigParse   *parse,
		    const FcChar8   *binding_string,
		    FcValueBinding  *binding_ret)
{
    FcValueBinding binding;

    if (!binding_string)
	binding = FcValueBindingWeak;
    else
    {
	if (!strcmp ((char *) binding_string, "weak"))
	    binding = FcValueBindingWeak;
	else if (!strcmp ((char *) binding_string, "strong"))
	    binding = FcValueBindingStrong;
	else if (!strcmp ((char *) binding_string, "same"))
	    binding = FcValueBindingSame;
	else
	{
	    FcConfigMessage (parse, FcSevereWarning, "invalid binding \"%s\"", binding_string);
	    return FcFalse;
	}
    }
    *binding_ret = binding;
    return FcTrue;
}
