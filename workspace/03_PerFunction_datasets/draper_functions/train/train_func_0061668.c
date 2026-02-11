FcConfigLexBool (FcConfigParse *parse, const FcChar8 *bool_)
{
    FcBool  result = FcFalse;

    if (!FcNameBool (bool_, &result))
	FcConfigMessage (parse, FcSevereWarning, "\"%s\" is not known boolean",
			 bool_);
    return result;
}
