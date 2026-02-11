develop_kvalues(va_list val, ErrorHandler *errh)
{
  if (!cp_values || !cp_parameter_used)
    return errh->error("out of memory in cp_va_kparse");

  while (1) {

    if (nvalues == cp_values_size - 1)

      return errh->error("too many arguments to cp_va_kparse!");

    cp_value *v = &cp_values[nvalues];
    v->argtype = 0;
    v->keyword = va_arg(val, const char *);
    if (v->keyword == 0)
	goto done;
    else if (v->keyword[0] == '\377' && strcmp(v->keyword, cpIgnoreRest) == 0) {
	ignore_rest = true;
	goto done;
    }
    int flags = va_arg(val, int);
    if ((flags & cpkPositional) && npositional >= 0)
	return errh->error("%s: positional arguments must be grouped at the beginning", v->keyword);
    if ((flags & (cpkPositional | cpkMandatory)) == (cpkPositional | cpkMandatory)
	&& nrequired >= 0)
	return errh->error("%s: mandatory positional arguments must precede optional ones", v->keyword);
    if (npositional < 0 && !(flags & cpkPositional))
	npositional = nvalues;
    if (nrequired < 0 && (flags & (cpkPositional | cpkMandatory)) != (cpkPositional | cpkMandatory))
	nrequired = nvalues;
    if (flags & cpkConfirm) {
	v->store_confirm = va_arg(val, bool *);
	*v->store_confirm = false;
    } else
	v->store_confirm = 0;


    const char *command_name = va_arg(val, const char *);
    const cp_argtype *argtype = cp_find_argtype(command_name);
    if (!argtype)
      return errh->error("unknown argument type %<%s%>!", command_name);
    v->argtype = argtype;
    v->v.s32 = (flags & (cpkMandatory | cpkDeprecated));


    if (argtype->internal == cpiIgnore) {
	nvalues++;
	continue;
    } else if (argtype->internal >= 0 && argtype->internal <= cpiLastMagic)
	return errh->error("%s: bad magic command in cp_va_kparse", command_name + 1);


    v->description = "?";
    if (argtype->flags & cpArgExtraInt)
	v->extra.i = va_arg(val, int);
    else if (argtype->flags & cpArgExtraCStr) {
	if (!(v->extra.c_str = va_arg(val, const char *)))
	    return errh->error("missing extra parameter");
    }
    v->store = va_arg(val, void *);
    if (argtype->flags & cpArgStore2)
      v->store2 = va_arg(val, void *);
    nvalues++;
  }

 done:
  if (npositional < 0)
      npositional = nvalues;
  nrequired = 0;
  return 0;
}
