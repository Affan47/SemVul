CDUnmark(SymbolDesc)

struct s *SymbolDesc;
{
    struct g *GenDesc;
    struct o *Pointer;
    char *SymbolName;
    int NumX,NumY;
    int DX,DY;
    int Info;
    int Layer;
    struct s *MasterDesc;

    if (Not CDInitGen(SymbolDesc,0,-CDINFINITY,-CDINFINITY,CDINFINITY,
        CDINFINITY,&GenDesc)) return (CDError(CDMALLOCFAILED));
#ifdef DEBUG_CDUNMARK
fprintf(stderr,"\n\n");
fprintf(stderr,"1CDUnmark: Inititialezed generator on instance layer.\n\n");
#endif
    loop {
        CDGen(SymbolDesc,GenDesc,&Pointer);
        if (Pointer == NULL)
            break;

#ifdef DEBUG_CDUNMARK
fprintf(stderr,"2CDUnmark: CDGen found instance: Pointer = 0x%x\n\n",Pointer);
#endif

        CDCall(Pointer,&SymbolName,&NumX,&DX,&NumY,&DY);

#ifdef DEBUG_CDUNMARK
fprintf(stderr,"3CDUnmark: instance name = %s\n\n",SymbolName);
#endif


        if (Not CDOpen(SymbolName,&MasterDesc,'r'))
            return (CDError(CDMALLOCFAILED));

#ifdef DEBUG_CDUNMARK
fprintf(stderr,"4CDUnmark: CDOpen returned MasterDesc = 0x%x\n\n",MasterDesc);
#endif

        CDInfo(MasterDesc,(struct o *)NULL,&Info);
        if (Info != 0) {

            CDSetInfo(MasterDesc,(struct o *)NULL,0);
            if (Not CDUnmark(MasterDesc))
                return (False);
        }
    }
    for (Layer = 1; Layer <= CDNUMLAYERS; ++Layer) {
        if (Not CDInitGen(SymbolDesc,Layer,-CDINFINITY,-CDINFINITY,
            CDINFINITY,CDINFINITY,&GenDesc))
            return (CDError(CDMALLOCFAILED));

#ifdef DEBUG_CDUNMARK
fprintf(stderr,"5CDUnmark: Inititialezed generator on layer %d.\n\n",Layer);
#endif

        loop{
            CDGen(SymbolDesc,GenDesc,&Pointer);
            if (Pointer == NULL)
                break;

#ifdef DEBUG_CDUNMARK
fprintf(stderr,"6CDUnmark: CDGen found instance: Pointer = 0x%x\n\n",Pointer);
#endif

            CDInfo(SymbolDesc,(struct o *)NULL,&Info);
            if (Info != 0) {

                CDSetInfo(SymbolDesc,Pointer,0);
            }
        }
    }
    return (True);
}
