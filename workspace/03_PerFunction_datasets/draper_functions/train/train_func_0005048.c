_dxf_ExMacroRecursionPop (char *name, _ntype type)
{
    if (type != NT_MACRO)
	return;

    if (--_macro_depth < 0)
	_macro_depth = 0;
}
