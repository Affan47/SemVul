ajSeqSetNuc(AjPSeq thys)
{
    if(ajStrMatchC(thys->Type, "N"))
      return;

    ajStrAssignC(&thys->Type, "N");

    if(thys->Fttable)
	ajFeattableSetNuc(thys->Fttable);


    ajStrExchangeSetCC(&thys->Seq,
		       "xX",
		       "nN");

    return;
}
