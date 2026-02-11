generateVBargraph(Tree sig, Tree path, Tree min, Tree max, const string& exp)
{
	string varname = getFreshID("{u_g}");

	Type t = getCertifiedSigType(sig);
	switch (t->variability()) {

		case kKonst :
			break;

		case kBlock :
			break;

		case kSamp :
			break;
	}
    return generateCacheCode(sig, varname);
}
