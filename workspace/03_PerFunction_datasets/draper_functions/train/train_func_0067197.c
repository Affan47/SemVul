featTagSpecialAllInference(const AjPStr val)
{
    AjPStr typstr = NULL;
    ajint i;
    AjBool ret = ajFalse;
    AjBool ok;
    const char* types[] =
    {
	"non-experimental evidence, no additional details recorded",
	"similar to sequence",
	"similar to AA sequence",
	"similar to AA sequence sequence",
	"similar to DNA sequence",
	"similar to RNA sequence",
	"similar to RNA sequence, mRNA",
	"similar to RNA sequence,mRNA",
	"similar to RNA sequence, EST",
	"similar to RNA sequence, other RNA",
	"profile",
	"nucleotide motif",
	"protein motif",
	"ab initio prediction",
        "alignment",
	NULL
    };

    if(!featRegSpecialInference)
	featRegSpecialInference = ajRegCompC("^([^:]+)(:([^:]+)?)*$");

    if(ajRegExec(featRegSpecialInference, val))
    {
	ret = ajTrue;
	ajRegSubI(featRegSpecialInference, 1, &typstr);

	ok = ajFalse;
	for(i=0; types[i]; i++)
	{
	    if(ajStrPrefixC(typstr, types[i]))
	    {
		if(ajStrMatchC(typstr, types[i]))
		{
		    ok = ajTrue;
		    break;
		}

		if(ajStrSuffixC(typstr, " (same species)"))
		{
		    if(ajStrGetLen(typstr) == strlen(types[i]) + 15)
		    {
			ok = ajTrue;
			break;
		    }
		}

		else if(ajStrSuffixC(typstr, "(same species)"))
		{
		    if(ajStrGetLen(typstr) == strlen(types[i]) + 14)
		    {
			ok = ajTrue;
			break;
		    }
		}

                else if(ajStrSuffixC(typstr, " (same species) "))
		{
		    if(ajStrGetLen(typstr) == strlen(types[i]) + 16)
		    {
			ok = ajTrue;
			break;
		    }
		}
	    }
	}

	if(!ok)
	    ret = ajFalse;
    }

    if(!ret)
	ajFeatWarn("bad /inference value '%S' type: '%S'", val, typstr);

    ajStrDel(&typstr);
    return ret;
}
