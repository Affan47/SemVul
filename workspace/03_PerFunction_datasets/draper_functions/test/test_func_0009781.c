antlr3TokenFactoryNew(pANTLR3_INPUT_STREAM input)
{
    pANTLR3_TOKEN_FACTORY   factory;


    factory	= (pANTLR3_TOKEN_FACTORY) ANTLR3_MALLOC((size_t)sizeof(ANTLR3_TOKEN_FACTORY));

    if	(factory == NULL)
    {
	return	NULL;
    }


    factory->newToken	    =  newPoolToken;
    factory->close			=  factoryClose;
    factory->setInputStream = setInputStream;


    factory->thisPool	= -1;
    factory->pools      = NULL;
    newPool(factory);


    antlr3SetTokenAPI(&factory->unTruc);


    factory->unTruc.factoryMade	= ANTLR3_TRUE;


    setInputStream(factory, input);

    return  factory;

}
